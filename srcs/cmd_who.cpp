/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_who.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichougragrani <ichougragrani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 11:38:20 by ichougra            #+#    #+#             */
/*   Updated: 2022/01/21 03:23:50 by ichougra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void			who_in_chan(t_env *e, int cs, char **input_arr)
{
	int			i;

	i = 0;
	if (ft_arrlen(input_arr) > 1)
	{
		strcpy(e->fds[cs].buf_write, "\033[31m==\033[0m Usage: /who\n");
		return ;
	}
	while (i <= e->max)
	{
		if (e->fds[i].type == FD_CLIENT && \
		!strcmp(e->fds[i].user.channel, e->fds[cs].user.channel))
		{
			strcat(e->fds[cs].buf_write, "\033[31m> \033[0m");
			strcat(e->fds[cs].buf_write, e->fds[i].user.nickname);
			strcat(e->fds[cs].buf_write, "\n");
		}
		i++;
	}
}
