/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrahimchougrani <ibrahimchougrani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 11:24:05 by ichougra          #+#    #+#             */
/*   Updated: 2022/01/24 00:33:31 by ibrahimchou      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

Server::Server(std::string host, std::string port, std::string pass)
{
    _host = host;
    _port = port;
    _portIn = atoi(port.c_str());
    _password = pass;

	init_env(&this->env);
	
   	createSocket();
    _serverName = _host;
}

Server::~Server() {}
//------------------------------------------------------------------

void Server::start()
{
	
	std::cout << BOLDGREEN  << "============SERVER INIT SUCCESS !!==============" << RESET << std::endl;
	std::cout << YELLOW << "Waiting for clients ..." << RESET << std::endl;

	run_server(&this->env);
}

void	srv_accept(t_env *e, int i)
{
	char	concat[NICK_SIZE + 9 + CHAN_SIZE];

	i = 0;
	e->cslen = sizeof(e->csin);
	get_time(e);
	
	if ((e->cs = accept(e->sock, (struct sockaddr *)&e->csin, &e->cslen)) < 0)
		printf("\033[31m[%s]\033[0m Client connection failed", e->strtime);
	
	init_client(e);
	
	std::string str = "\033[1;30m- Connected to 127.0.0.1:" + e->port + '\n';
	send(e->cs, str.c_str(), str.length(), 0);
	
	send(e->cs, "\033[1;31m /help \033[0m\033[1;36m: list of commmands\033[0m\n", 50, 0);
	

	std::cout << "\033[31m[" << e->strtime << "]\33[0m" << BOLDWHITE << " ✅ New client #" << e->cs << " from @" << inet_ntoa(e->csin.sin_addr) << ":" << e->port << RESET << std::endl;
	printf("\033[31m[%s]\033[0m %s joined %s\n", e->strtime, e->fds[e->cs].user.nickname, e->fds[e->cs].user.channel);
	
	memset(concat, 0, NICK_SIZE + 9 + CHAN_SIZE);
	
	strcpy(concat, e->fds[e->cs].user.nickname);
	strcat(concat, " joined ");
	strcat(concat, e->fds[e->cs].user.channel);
	strcat(concat, "\n");
	
	e->max++;
	
	send_to_chan(e, concat, MSG_INFO, e->cs);
}