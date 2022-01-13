/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichougra <ichougra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:21:21 by ibrahimchou       #+#    #+#             */
/*   Updated: 2022/01/11 15:08:43 by ichougra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h> 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <iostream>
#include <sys/select.h>
#include <sys/time.h>

#define PORT 30000
#define BUFSIZE 4096
#define SOCKETERROR -1

typedef struct User
{
    char name[30];
    int age;
}User;

int check(int exp, char const *msg)
{
    if (exp == -1)
    {
        perror(msg);
        exit (1);
    }
    return (exp);
}

int setup_server(int port)
{
    int opt = 1, socketServer;
    struct sockaddr_in addrServer; // struct pour configurer l'addresse du serveur

    check((socketServer = socket(AF_INET, SOCK_STREAM, 0)), "ERROR: opening socket");
    check((setsockopt(socketServer, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(int))), "setsockopt(SO_REUSEADDR) failed");

    addrServer.sin_addr.s_addr = inet_addr("127.0.0.1"); //attribuer laddresse
    addrServer.sin_family = AF_INET; // type d'addresse
    addrServer.sin_port = htons(port); // choisir le port

    check((bind(socketServer, (const struct sockaddr *)&addrServer, sizeof(addrServer))), "Bind Failed!");
    printf("Bind : %d\n", socketServer);

    check((listen(socketServer, 1)), "Listen Failed!");
    printf("listen\n");

    return socketServer;
}

int accept_connec(int socketServ)
{
    struct sockaddr_in addrClient;
    socklen_t csize = sizeof(addrClient);
    int socketClient;

    check((socketClient = accept(socketServ, (struct sockaddr *)&addrClient, &csize)), "Accept Failed!\n");

    return socketClient;
}

void *handle_connect(int socketClient)
{
    char buffer[BUFSIZE];
    size_t bytes_read;
    int msgsize = 0;
    char actualpath[PATH_MAX + 1];

    //read the client's message -- the name of the file to read
    while ((bytes_read = read(socketClient, buffer + msgsize, sizeof(buffer) - msgsize -1)))
    {
        msgsize += bytes_read;
        if (msgsize > BUFSIZE - 1 || buffer[msgsize - 1] == '\n') 
            break;
    }
    check(bytes_read, "recv error");
    buffer[msgsize - 1] = 0; //NULL terminate the message and remove the \n

    std::cout << "REQUES: " << buffer << "\n";
    fflush(stdout);

    //validity check
    if (realpath(buffer, actualpath) == NULL)
    {
        std::cout << "ERROR(bad path): " << buffer << "\n";
        close(socketClient);
        return NULL;
    }

    //read file and send its contents to client
    FILE *fp = fopen(actualpath, "r");
    if (fp == NULL)
    {
        std::cout << "ERROR(open): " << buffer << "\n";
        close(socketClient);
        return NULL;
    }

    //read file contents and send them to client
    //note this is a fine example program, but rather insecure.
    //a real program would probably limit the client to certain file
    while ((bytes_read = fread(buffer, 1, BUFSIZE, fp)) > 0)
        write(socketClient, buffer, bytes_read);
    close(socketClient);
    fclose(fp);
    std::cout << "closing connection\n";
    return NULL;
}

int main(int ac, char **av)
{
    int socketServer = setup_server(PORT);

    int max_socket_so_far = 0;
    fd_set current_socket, ready_socket;
    
    //initialize my current set
    FD_ZERO(&current_socket);
    FD_SET(socketServer, &current_socket);
    max_socket_so_far = socketServer;

    while (true)
    {
        std::cout << "Waiting for connections...\n";
        
        //because select is destructive
        ready_socket = current_socket;
        if (select(max_socket_so_far, &ready_socket, NULL, NULL, NULL) < 0)
        {
            perror("select error");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < max_socket_so_far; i++)
        {
            if (FD_ISSET(i, &ready_socket))
            {
                if (i == socketServer)
                {
                    //this is a new connection
                    int socketClient = accept_connec(socketServer);
                    FD_SET(socketClient, &current_socket);
                    printf("Accept\n");
                } else {
                    //do whatever we do with connections.
// -------------------handle_connect(i);--------------------------------------------- FONCTION A REFAIRE
                    FD_CLR(i, &current_socket);
                }
            }
        }
    }

    // User user = {
    //     .name = "TOMATE",
    //     .age = 19
    // }; // info a envoyer
    // send(socketClient, &user, sizeof(user), 0); 

    // close(socketClient);
    // close(socketServer);
    // std::cout << "close\n";

    return 0;
}