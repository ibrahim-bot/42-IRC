/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichougra <ichougra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 12:34:46 by ichougra          #+#    #+#             */
/*   Updated: 2022/01/06 17:15:17 by ichougra         ###   ########.fr       */
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

typedef struct User
{
    char name[30];
    int age;
}User;

int main()
{
    //------------------RIEN DE NOUVEAU--------------------
    int socketClient = socket(AF_INET, SOCK_STREAM, 0); // creer une socket de connexion;
    
    struct sockaddr_in addrClient; // struct d'addresse serveur 
    addrClient.sin_addr.s_addr = inet_addr("127.0.0.1"); // attribuer laddress
    addrClient.sin_family = AF_INET; // type d'addresse (ipv4)
    addrClient.sin_port = htons(30000); // port de connection
    //-----------------------------------------------------
    
    connect(socketClient, (const struct sockaddr *)&addrClient, sizeof(addrClient)); //connecter le server a la socket
    printf("connect\n");

    User user;
    recv(socketClient, &user, sizeof(User), 0);
//recevoir les donnes; du client qui est connecter au server; addresse ou mettre les donnees; taille des donnés;

    printf("Name = %s \nAge = %d\n", user.name, user.age);//afficher les info
    close(socketClient); // ne pas oubllie de fermer le socket
    return (0);
}