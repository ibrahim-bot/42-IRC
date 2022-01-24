/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichougragrani <ichougragrani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 00:27:21 by ichougra       #+#    #+#             */
/*   Updated: 2022/01/23 07:10:02 by ichougra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void Server::getAddr()
{
    struct addrinfo hints;
	
	std::cout << "Server information initialization...\t";
	memset(&hints, 0, sizeof(hints));

	hints.ai_family   = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags    = AI_PASSIVE;

	if (getaddrinfo(_host.c_str(), _port.c_str(), &hints, &servinfo) != 0)
	{
		std::cout << RED << " KO" << RESET << std::endl;
		throw std::runtime_error("error: getaddrinfo");
	}
	std::cout << GREEN << "OK" << RESET << std::endl;
}

int Server::setSocket(struct addrinfo *p)
{
    struct protoent *proto;
    int	y = 1;

    if (!(proto = getprotobyname("tcp")))
		throw std::runtime_error("error: getProtobyname");

	std::cout << "Creating socket...\t\t\t";
                                                    //p->ai_protocol
	if ((_sock = socket(p->ai_family, p->ai_socktype, proto->p_proto)) == -1) {
		std::cout << RED << "KO" << RESET << std::endl;
		return 1;
	}

	if (setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR, &y, sizeof(int)) == -1) {
		std::cout << RED << "KO" << RESET << std::endl;
		close(_sock);
		freeaddrinfo(servinfo);
		throw std::runtime_error("error: setsockopt");
	}
	
	if (fcntl(_sock, F_SETFL, O_NONBLOCK) == -1) {
		std::cout << RED << "KO" << RESET << std::endl;
		throw std::runtime_error("Error: fcntl");
	}
	
	std::cout << GREEN << "OK" << RESET << std::endl;
	return (0);
}

int	Server::setBind(struct addrinfo *p)
{
    // struct sockaddr_in	sin;
        
    // sin.sin_family = AF_INET;
    // sin.sin_addr.s_addr = inet_addr(_host.c_str());
    // sin.sin_port = htons(_portIn);

 	std::cout << "Binding port " << _port << "...\t\t\t";
	 
	if (bind(_sock, p->ai_addr, p->ai_addrlen) < 0)
	{
		std::cout << RED << "KO" << RESET << std::endl;
		close(_sock);
		return 1;
	}
	std::cout << GREEN << "OK" << RESET << std::endl;
	return 0;
}

void	Server::createSocket()
{
    struct addrinfo *p;

	this->getAddr();
    for (p = servinfo; p != NULL; p = p->ai_next)
    {
		if (setSocket(p))
			continue ;
		if (setBind(p))
			continue;
		break;
    }
	freeaddrinfo(servinfo);
	if (!p)
		throw std::runtime_error("error: failed to find address");
	
	if (listen(_sock, MAX_CONNECTION) == -1)
		throw std::runtime_error("error: listen");
    env.sock = _sock;
	env.port = _port;
    env.fds[_sock].type = FD_SERV;
    env.fds[_sock].fct_read = srv_accept;
}
