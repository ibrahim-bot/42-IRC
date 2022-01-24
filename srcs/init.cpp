/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrahimchougrani <ibrahimchougrani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 23:57:35 by ibrahimchou       #+#    #+#             */
/*   Updated: 2022/01/23 23:57:42 by ibrahimchou      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void				Server::init_env(t_env *env)
{
	int i = 0; 
	struct rlimit	rlp;

	if (getrlimit(RLIMIT_NOFILE, &rlp) > 0)
		throw std::runtime_error("Error: getrlimit: failed");

	env->maxfd = rlp.rlim_cur;

	if (!(env->fds = (t_fd *)malloc(sizeof(*env->fds) * env->maxfd)))
		throw std::runtime_error("Error: Malloc failed");
	
	while (i <= MAX_CONNECTION + 10000)
	{
		clean_fd(i, env);
		i++;
	}
}

void	init_client(t_env *e)
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