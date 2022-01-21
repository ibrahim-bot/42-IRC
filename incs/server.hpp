/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrahimchougrani <ibrahimchougrani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 10:29:21 by hivian            #+#    #+#             */
/*   Updated: 2022/01/21 03:41:38 by ibrahimchou      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

// # include "../libft/incs/libft.h"
# include <stdio.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <dirent.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/select.h>
# include <sys/time.h>
# include <stdbool.h>
# include "colors.hpp"
# include <iostream>
#include <exception>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unistd.h>

# define BUF_SIZE	512
# define NICK_SIZE	9
# define CHAN_SIZE	200

# define CHAN_GEN	"#_General"

# define DATE_SIZE	26

# define FD_SERV	1
# define FD_CLIENT	2

# define MSG_INFO	0
# define MSG_STD	1

# define MAX(a,b)	((a > b) ? a : b)

# define MAX_CONNECTION 42

typedef struct sockaddr_in	t_sockaddr_in;

typedef struct		s_user
{
	char			channel[CHAN_SIZE + 1];
	char			nickname[NICK_SIZE + 1];
}					t_user;

typedef struct s_env t_env;

typedef struct		s_fd
{
	int				type;
	void			(*fct_read)(t_env *, int i);
	void			(*fct_write)(t_env *, int i);
	char			buf_read[BUF_SIZE + 1];
	char			buf_write[BUF_SIZE + 1];
	t_user			user;
}					t_fd;

typedef struct		s_env
{
	t_fd			*fds;
	
	t_sockaddr_in	csin;
	socklen_t		cslen;
	
	int				port;
	int				sock;

	int				cs;
	
	int				maxfd;
	int				max;
	int				ret;
	int				ret_recv;
	
	fd_set			fd_read;
	fd_set			fd_write;
	
	char			strtime[DATE_SIZE];
}					t_env;

class Server
{
	private:
		int				_sock;
		int				_portIn;
		
		std::string		_host;
		std::string		_port;
		std::string		_password;
		std::string		_serverName;
		
		struct addrinfo *servinfo;
		
		t_env			env;

		Server();

		void			createSocket();
		void			getAddr();
		int				setSocket(struct addrinfo *p);
		int				setBind(struct addrinfo *p);


	public:
		Server(std::string, std::string, std::string);
		virtual ~Server();

		void start();
};

void				change_nick(t_env *e, int cs, char **input_arr);
void				check_fd(t_env *e);
void				clean_fd(int i, t_env *e);
int					duplicate_user(t_env *e, int cs, char *name);
int					get_fd_from_usr(t_env *e, char *name);
void				get_time(t_env *e);
void				init_env(t_env *e);
void				init_fd(t_env *e);
void				join_chan(t_env *e, int cs, char **inp_arr);
void				leave_chan(t_env *e, int cs, char **input_arr);
void				print_error(char *str);
void				ring_buffer_read(t_env *e, int cs, char *msg);
void				ring_buffer_write(t_env *e, int cs, char *msg);
void				run_cmd(t_env *e, int cs, char *buf);
void				send_msg(t_env *e, char **input_arr, int cs);
void				send_to_chan(t_env *e, char *message, int msg_type, int cs);
void				srv_accept(t_env *e, int i);
void				who_in_chan(t_env *e, int cs, char **input_arr);

char	*ft_strtrim(char const *s);
int			ft_arrlen(char **array);
void	run_server(t_env *e);
#endif
