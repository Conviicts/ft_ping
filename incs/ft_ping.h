/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 04:04:31 by jode-vri          #+#    #+#             */
/*   Updated: 2022/12/12 12:57:34 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <netinet/ip_icmp.h>
# include <netinet/icmp6.h>
# include <netinet/ip6.h>
# include <netinet/ip.h>
# include <signal.h>
# include <sys/time.h>
# include <errno.h>
# include <math.h>
# include <float.h>

# include "libft.h"

typedef struct s_connexion {
	struct addrinfo	hints;
	struct addrinfo	*res;
	int				fd;
	USHORT			seq;
	UINT			ttl;
	double			duration_min;
	double			duration_max;
	double			total;
	double			ratio;
}	t_connexion;

typedef struct s_opts {
	int				version;
	int				verbose;
	int				help;
	int				ttl;
	int				timeout;
	int				interval;
	ULONG			limit;
	t_bool			need_timeout;
}	t_opts;

typedef struct s_target {
	t_opts			opts;
	t_connexion		conn;
	pid_t			pid;
	char			*hostname;
	char			*source;
	char			*destination;

	struct ip		*ip;
	struct icmp		*icmp;
	ULONG			send_count;
	char			buf[76];

	int				recv_count;
	struct iovec	iov[1];
	struct msghdr	msg;
	char			buf_control[1000];
}	t_target;

t_target	*g_t;

void	pexit(char *s);

t_bool	check_value(char *v);
t_bool	is_empty(char *option, char c);
void	calculate_duration(t_target *t, double duration);

int		parse_options(t_target *target, int ac, char **av);
char	*hostname_to_ip(char *s);
USHORT	icmp_checksum(USHORT *data, int len);

void	connect_socket(t_target *t);

void	sigint_handler(int c);
void	sigalrm_handler(int c);

void	loop(t_target *t);
void	init_send(t_target *t, USHORT id, USHORT seq);
void	init_recv(t_target *t);

void	print_help(void);
void	print_intro(t_target *t);
void	print_info(t_target *t, int length, double duration);
void	print_stats(t_target *t);
#endif
