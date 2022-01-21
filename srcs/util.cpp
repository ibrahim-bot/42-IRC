/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrahimchougrani <ibrahimchougrani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 16:49:16 by hivian            #+#    #+#             */
/*   Updated: 2022/01/21 03:21:22 by ibrahimchou      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void				get_time(t_env *e)
{
	time_t			timer;
	struct tm		*tm_info;

	time(&timer);
	tm_info = localtime(&timer);
	strftime(e->strtime, DATE_SIZE, "%Y-%m-%d %H:%M:%S", tm_info);
}

int					duplicate_user(t_env *e, int cs, char *name)
{
	int				i;

	i = 0;
	while (i <= e->max)
	{
		if (!strcmp(e->fds[i].user.nickname, name) && i != cs)
			return (1);
		i++;
	}
	return (0);
}

int					get_fd_from_usr(t_env *e, char *name)
{
	int				i;

	i = 0;
	while (i <= e->max)
	{
		if (!strcmp(e->fds[i].user.nickname, name))
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strtrim(char const *s)
{
	char	*str;
	size_t	len;

	if (!s)
		return (NULL);
	while (*s == ' ' || *s == '\n' || *s == '\t')
		s++;
	len = strlen(s);
	while (s[len - 1] == ' ' || s[len - 1] == '\n' || s[len - 1] == '\t')
		len--;
	str = strndup(s, len);
	return (str);
}

int			ft_arrlen(char **array)
{
	int		i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}