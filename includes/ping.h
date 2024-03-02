/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 06:09:54 by jode-vri          #+#    #+#             */
/*   Updated: 2024/03/02 20:45:32 by jode-vri         ###   ########.fr       */
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

typedef struct s_options {
	bool	verbose;
	bool	help;

	unsigned int	interval;
	unsigned int	timeout;
	unsigned int	ttl;
}	t_options;

typedef struct s_ping {
	char		*hostname;
	char		*destination;
	char 		*source;
	pid_t		pid;
	int			fd;
	t_options	options;
}	t_ping;

char	*get_hostname(char *hostname);
bool	init_socket(t_ping *ping);

#endif