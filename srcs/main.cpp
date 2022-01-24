/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrahimchougrani <ibrahimchougrani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 10:30:39 by ichougra          #+#    #+#             */
/*   Updated: 2022/01/23 23:57:19 by ibrahimchou      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void	run_server(t_env *e)
{
	while (true)
	{
		init_fd(e);
		e->ret = select(e->max + 1, &e->fd_read, &e->fd_write, NULL, 0);
		check_fd(e);
	}
}

int	main(int ac, char **av)
{
	try {
        if (ac != 3)
            throw std::runtime_error("Usage: ./ircserv <port> <password>");
		if (ac == 3)
		{
			Server serv("127.0.0.1", av[1], av[2]);
			serv.start();
		} 
	 } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
	}
	return (0);
}
