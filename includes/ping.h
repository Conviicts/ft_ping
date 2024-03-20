/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 06:09:54 by jode-vri          #+#    #+#             */
/*   Updated: 2024/03/20 09:26:20 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PING_H
#define PING_H

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <errno.h>
#include <signal.h>

#define PACKET_SIZE	56

typedef struct s_options {
	bool	verbose;
	bool	help;

	unsigned int	interval;
	unsigned int	timeout;
	unsigned int	ttl;
}	t_options;

typedef struct s_packet {
	struct icmp	icmp;
	time_t		time;
	char		data[PACKET_SIZE];
}	t_packet;

typedef struct	s_dest {
	char				*hostname;
	int					family;
	// struct sockaddr_in	*sa_in;
	struct addrinfo		*res;
	char				ip[INET_ADDRSTRLEN];
}		t_dest;

typedef struct s_stats {
	int				transmitted;
	struct timeval	tv_start;
	struct timeval	tv_end;
}	t_stats;

typedef struct s_ping {
	int			fd;
	bool		wait;
	t_options	options;
	t_dest		dest;
	t_stats		stats;
}	t_ping;

extern struct s_ping	*g_ping;

bool	parse_options(t_ping *ping, int ac, char **av);

void    signal_handler(int sig);
int		init_socket();

void    loop(t_ping *ping);

#endif