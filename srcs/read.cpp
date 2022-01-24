/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichougragrani <ichougragrani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 06:38:56 by ichougra       #+#    #+#             */
/*   Updated: 2022/01/23 10:49:13 by ichougra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void	server_read(t_env *e, int i)
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
		std::cout << RED << "[" << e->strtime << "]" << RESET << BOLDWHITE <<\
		" ❌ Client #" << i << " gone away" << RESET << std::endl;
	}
	else
	{
		e->fds[i].buf_read[e->ret_recv] = '\0';
		ring_buffer_read(e, i, e->fds[i].buf_read);
		memset(e->fds[i].buf_read, 0, BUF_SIZE + 1);
	}
}
