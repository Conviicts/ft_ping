/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 20:38:17 by jode-vri          #+#    #+#             */
/*   Updated: 2024/03/20 09:25:55 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ping.h"

int		init_socket() {
	int		fd;

	if ((fd = socket(g_ping->dest.res->ai_family, g_ping->dest.res->ai_socktype, g_ping->dest.res->ai_protocol)) == -1) {
		perror("socket");
		//TODO: exit properly
		exit(EXIT_FAILURE);
	}
	if (setsockopt(fd, IPPROTO_IP, IP_TTL, &g_ping->options.ttl, sizeof(g_ping->options.ttl)) == -1) {
		perror("setsockopt");
		//TODO: exit properly
		exit(EXIT_FAILURE);
	}
	return (fd);
}