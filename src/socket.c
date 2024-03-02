/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 20:38:17 by jode-vri          #+#    #+#             */
/*   Updated: 2024/03/02 20:45:23 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ping.h"

bool	init_socket(t_ping *ping) {
	if ((ping->fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) == -1) {
		printf("ft_ping: socket failed %s\n", strerror(errno));
		return (false);
	}
	if (setsockopt(ping->fd, IPPROTO_IP, IP_TTL, &ping->options.ttl, sizeof(ping->options.ttl)) == -1) {
		printf("ft_ping: setsockopt failed %s\n", strerror(errno));
		close(ping->fd);
		return (false);
	}
	return (true);
}