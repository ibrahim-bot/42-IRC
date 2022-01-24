/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichougragrani <ichougragrani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 15:01:44 by ichougra            #+#    #+#             */
/*   Updated: 2022/01/23 23:22:44 by ichougra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

static void		print_help(t_env *e, int cs)
{
	// if (ft_arrlen(&input_arr) != 1)
	// {
	// 	strcpy(e->fds[cs].buf_write, "\033[31m==\033[0m Unknow command\n");
	// 	return ;
	// }
	strcpy(e->fds[cs].buf_write,
		"===================== - List of commands - ====================\n");
	strcat(e->fds[cs].buf_write,
		"\033[31m> \033[0m    /help : Print a list of commands\n");
	strcat(e->fds[cs].buf_write,
		"\033[31m> \033[0m    /nick <nickname>\n");
	strcat(e->fds[cs].buf_write,
		"\033[31m> \033[0m    /join <#channel>, /leave [#channel]\n");
	strcat(e->fds[cs].buf_write,
		"\033[31m> \033[0m    /who : Print all nickname\n");
	strcat(e->fds[cs].buf_write,
		"\033[31m> \033[0m    /msg <nick> <message> : send private msg\n");
	strcat(e->fds[cs].buf_write,
		"\033[31m> \033[0m    /ignore\n");
	strcat(e->fds[cs].buf_write,
		"\033[31m> \033[0m    /ignore <nick>\n");
	strcat(e->fds[cs].buf_write,
		"\033[31m> \033[0m    /unignore <nick>\n");
	strcat(e->fds[cs].buf_write,
		"===============================================================\n");
}

void			send_to_chan(t_env *e, char *message, int msg_type, int cs)
{
	int			i;

	i = 0;
	while (i <= e->max)
	{
		if (e->fds[i].type == FD_CLIENT && (!strcmp(e->fds[i].user.channel, e->fds[cs].user.channel)))
		{
			if (msg_type == MSG_INFO)
			{
				strcpy(e->fds[i].buf_write, "\033[31m==\033[0m ");
				strcat(e->fds[i].buf_write, message);
			}
			else if (i != cs)
			{
				strcpy(e->fds[i].buf_write, "\033[33m<");
				strcat(e->fds[i].buf_write, e->fds[cs].user.nickname);
				strcat(e->fds[i].buf_write, ">\033[0m ");
				strcat(e->fds[i].buf_write, message);
			}
		}
		i++;
	}
}

void			run_cmd(t_env *e, int cs, char *buf)
{
	char	**input_arr = NULL;

	input_arr = split(buf, ' ');
	if (!strncmp(buf, "/help", 5))
		print_help(e, cs);
	else if (!strncmp(input_arr[0], "/nick", 5))
		change_nick(e, cs, input_arr);
	else if (!strncmp(input_arr[0], "/msg", 4))
		send_msg(e, input_arr, cs);
	else if (!strncmp(input_arr[0], "/join", 5))
		join_chan(e, cs, input_arr);
	else if (!strncmp(input_arr[0], "/leave", 6))
		leave_chan(e, cs, input_arr);
	else if (!strncmp(input_arr[0], "/who", 4))
		who_in_chan(e, cs, input_arr);
	else if (strncmp(input_arr[0], "/connect", 4))
		strcpy(e->fds[cs].buf_write, "\033[31m==\033[0m Unknow command\n");
	//ft_arrdel(input_arr); FREE
	memset(e->fds[cs].buf_read, 0, BUF_SIZE + 1);
}
