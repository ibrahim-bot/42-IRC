/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_nick.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichougragrani <ichougragrani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 14:48:53 by ichougra            #+#    #+#             */
/*   Updated: 2022/01/21 03:22:35 by ichougra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

static int		is_valid_nick(char *nick)
{
	int			i;

	i = 0;
	while (nick[i] && nick[i] != '\n')
	{
		if (!isalnum(nick[i]))
			return (0);
		i++;
	}
	return (1);
}

static int		check_error(t_env *e, int cs, char **input_arr)
{
	if (ft_arrlen(input_arr) != 2)
	{
		strcpy(e->fds[cs].buf_write, \
			"\033[31m==\033[0m Usage: /nick <nickname>\n");
		return (-1);
	}
	else if (strlen(input_arr[1]) - 1 > NICK_SIZE)
	{
		strcpy(e->fds[cs].buf_write, \
			"\033[31m==\033[0m Nickname too long\n");
		return (-1);
	}
	else if (!is_valid_nick(input_arr[1]))
	{
		strcpy(e->fds[cs].buf_write, \
			"\033[31m==\033[0m Invalid character(s)\n");
		return (-1);
	}
	return (1);
}

void			change_nick(t_env *e, int cs, char **input_arr)
{
	char		tmp[NICK_SIZE + 1];
	char		concat[NICK_SIZE * 2 + 24];

	memset(tmp, 0, NICK_SIZE + 1);
	memset(concat, 0, NICK_SIZE * 2 + 24);
	if ((check_error(e, cs, input_arr)) < 0)
		return ;
	strncpy(tmp, input_arr[1], strlen(input_arr[1]) - 1);
	if (duplicate_user(e, cs, tmp))
	{
		strcpy(e->fds[cs].buf_write, \
			"\033[31m==\033[0m Nickname is already in use\n");
	}
	else
	{
		strcpy(concat, e->fds[cs].user.nickname);
		memset(e->fds[cs].user.nickname, 0, NICK_SIZE + 1);
		strcpy(e->fds[cs].user.nickname, tmp);
		strcat(concat, " has changed nick to ");
		strcat(concat, e->fds[cs].user.nickname);
		strcat(concat, "\n");
		send_to_chan(e, concat, MSG_INFO, cs);
	}
}
