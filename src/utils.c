/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 19:12:30 by jode-vri          #+#    #+#             */
/*   Updated: 2024/03/02 20:33:29 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ping.h"

char	*get_hostname(char *hostname) {
	struct addrinfo		hints;
	struct addrinfo		*res;
	struct sockaddr_in	*addr;
	char				*ip;

	ft_memset(&(hints), 0, sizeof(hints));
	hints.ai_family = AF_INET;
	if ((ip = malloc(INET_ADDRSTRLEN)) == NULL) {
		printf("malloc failed\n");
		exit(1);
	}
	if (getaddrinfo(hostname, NULL, &hints, &(res)) < 0) {
		printf("./ft_ping: unknown host\n");
		free(ip);
		exit(1);
	}
	addr = (struct sockaddr_in *)res->ai_addr;
	inet_ntop(res->ai_family, &(addr->sin_addr), ip, INET_ADDRSTRLEN);
	freeaddrinfo(res);
	return (ip);
}