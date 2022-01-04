/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrahimchougrani <ibrahimchougrani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:23:07 by ibrahimchou       #+#    #+#             */
/*   Updated: 2022/01/04 12:25:34 by ibrahimchou      ###   ########.fr       */
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

typedef struct User
{
    char name[30];
    int age;
}User;

int main(void)
{
    int socketServer = socket(AF_INET, SOCK_STREAM, 0); //creer une socket; AF_INET = IPv4; SOCK_STREAM = TCP; PROTOCOL = 0
    struct sockaddr_in addrServer; // struct pour configurer l'addresse du serveur

    addrServer.sin_addr.s_addr = inet_addr("127.0.0.1"); //attribuer laddresse
    addrServer.sin_family = AF_INET; // type d'addresse
    addrServer.sin_port = htons(30000); // choisir le port

    bind(socketServer, (const struct sockaddr *)&addrServer, sizeof(addrServer)); // connecter le serveur au reseau; le serveur a connecter; un pointeur sur sockaddr; taille du addrserveur 
    printf("Bind : %d\n", socketServer);

    listen(socketServer, 5); // serveur ecoute; nombre de client en connection
    printf("listen\n");

    struct sockaddr_in addrClient;
    socklen_t csize = sizeof(addrClient);
    int socketClient = accept(socketServer, (struct sockaddr *)&addrClient, &csize); // boucle infini a attendre q'un client ce connect
    printf("Accept\n");

    printf("client : %d\n", socketClient);

    User user = {
        .name = "TOMATE",
        .age = 19
    }; // info a envoyer
    send(socketClient, &user, sizeof(user), 0); // transmettre au coter client; par le socketClient; info a transmettre; taille des info

    close(socketClient);
    close(socketServer);
    std::cout << "close\n";

    return 0;
}