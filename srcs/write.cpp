/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichougragrani <ichougragrani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 06:40:58 by ichougra       #+#    #+#             */
/*   Updated: 2022/01/23 06:41:21 by ichougra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void    server_write(t_env *e, int i)
{
    send(i, e->fds[i].buf_write, strlen(e->fds[i].buf_write), 0);
    memset(e->fds[i].buf_write, 0, BUF_SIZE + 1);
}