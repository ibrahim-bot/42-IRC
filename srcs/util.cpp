/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichougragrani <ichougragrani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 16:49:16 by ichougra            #+#    #+#             */
/*   Updated: 2022/01/23 11:18:52 by ichougra      ###   ########.fr       */
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

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *dst;

	if (!s)
		return (NULL);
	dst = (char *)malloc(sizeof(char) * len + 1);
	if (!dst)
		return (NULL);
	dst = strncpy(dst, &s[start], len);
	dst[len] = '\0';
	return (dst);
}

char	**split(char const *s, char c)
{
	size_t	i;
	size_t	d;
	int		start;
	int		end;
	char	**tab;

	i = 0;
	d = 0;
	if (!s)
		return (NULL);
	if (!(tab = (char **)malloc(sizeof(*tab) * (strlen(s) / 2 + 2))))
		return (NULL);
	while (s[i] != '\0')
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		end = i;
		if (end > start)
			tab[d++] = ft_strsub(s, start, (end - start));
	}
	tab[d] = NULL;
	return (tab);
}