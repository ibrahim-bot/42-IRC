/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrahimchougrani <ibrahimchougrani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 11:24:05 by hivian            #+#    #+#             */
/*   Updated: 2022/01/21 03:53:05 by ibrahimchou      ###   ########.fr       */
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

static void	server_read(t_env *e, int i)
{
		char	concat[NICK_SIZE + 15];

		memset(concat, 0, NICK_SIZE + 15);
		
		if ((e->ret_recv = recv(i, e->fds[i].buf_read, BUF_SIZE, 0)) <= 0)
		{
			strcpy(concat, e->fds[i].user.nickname);
			strcat(concat, " disconnected\n");
			
			send_to_chan(e, concat, MSG_INFO, i);
			
			clean_fd(i, e);
			
			close(i);
			get_time(e);
			
			printf("\033[31m[%s]\033[0m Client #%d gone away\n", e->strtime, i);
		}
		else
		{
			e->fds[i].buf_read[e->ret_recv] = '\0';
			ring_buffer_read(e, i, e->fds[i].buf_read);
			memset(e->fds[i].buf_read, 0, BUF_SIZE + 1);
		}
}

static void				server_write(t_env *e, int i)
{
		send(i, e->fds[i].buf_write, strlen(e->fds[i].buf_write), 0);
		memset(e->fds[i].buf_write, 0, BUF_SIZE + 1);
}

static void				init_client(t_env *e)
{
	std::string cs_to_str;

	cs_to_str = std::to_string(e->cs);
	
	e->fds[e->cs].type = FD_CLIENT;
	
	e->fds[e->cs].fct_read = server_read;
	e->fds[e->cs].fct_write = server_write;

	strcpy(e->fds[e->cs].user.channel, CHAN_GEN);
	strcpy(e->fds[e->cs].user.nickname, "Guest");
	strcat(e->fds[e->cs].user.nickname, cs_to_str.c_str());
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
	
	send(e->cs, e->fds[e->cs].user.nickname, NICK_SIZE, 0);
	printf("\033[31m[%s]\033[0m New client #%d from %s:%d\n", e->strtime, e->cs,
	inet_ntoa(e->csin.sin_addr), ntohs(e->csin.sin_port));
	printf("\033[31m[%s]\033[0m %s joined %s\n", e->strtime, \
	e->fds[e->cs].user.nickname, e->fds[e->cs].user.channel);
	
	memset(concat, 0, NICK_SIZE + 9 + CHAN_SIZE);
	
	strcpy(concat, e->fds[e->cs].user.nickname);
	strcat(concat, " joined ");
	strcat(concat, e->fds[e->cs].user.channel);
	strcat(concat, "\n");
	
	e->max++;
	
	send_to_chan(e, concat, MSG_INFO, e->cs);
}