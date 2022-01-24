/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichougragrani <ichougragrani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 06:42:04 by ichougra       #+#    #+#             */
/*   Updated: 2022/01/23 06:43:15 by ichougra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void    clean_fd(int i, t_env *e)
{
	e->fds[i].type = 0;
	e->fds[i].fct_read = NULL;
	e->fds[i].fct_write = NULL;
	
	memset(e->fds[i].buf_write, 0, BUF_SIZE + 1);
	memset(e->fds[i].buf_read, 0, BUF_SIZE + 1);
	
	memset(e->fds[i].user.channel, 0, CHAN_SIZE + 1);
	memset(e->fds[i].user.nickname, 0, NICK_SIZE + 1);
}

void    check_fd(t_env *e)
{
	int	i = 0;

	while (i < e->maxfd && e->ret > 0)
	{
		if (FD_ISSET(i, &e->fd_read))
			e->fds[i].fct_read(e, i);

		if (FD_ISSET(i, &e->fd_write))
			e->fds[i].fct_write(e, i);

		if (FD_ISSET(i, &e->fd_read) || FD_ISSET(i, &e->fd_write))
			e->ret--;
		i++;
	}
}

void	init_fd(t_env *e)
{
	int	i = 0;
	
	e->max = 0;
	FD_ZERO(&e->fd_read);
	FD_ZERO(&e->fd_write);

	while (i < e->maxfd)
	{
		if (e->fds[i].type != 0)
		{
			FD_SET(i, &e->fd_read);
			if (strlen(e->fds[i].buf_write) > 0)
				FD_SET(i, &e->fd_write);
			e->max = MAX(e->max, i);
		}
		i++;
	}
}
