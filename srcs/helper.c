/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 12:25:10 by jode-vri          #+#    #+#             */
/*   Updated: 2022/12/12 12:57:24 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	calculate_duration(t_target *t, double duration)
{
	if (duration > t->conn.duration_max)
		t->conn.duration_max = duration;
	if (duration < t->conn.duration_min)
		t->conn.duration_min = duration;
	t->conn.total += duration;
	t->conn.ratio += duration * duration;
}

USHORT	icmp_checksum(USHORT *data, int len)
{
	ULONG	checksum;

	checksum = 0;
	while (len > 1)
	{
		checksum = checksum + *data++;
		len = len - sizeof(USHORT);
	}
	if (len)
		checksum = checksum + *(unsigned char *)data;
	checksum = (checksum >> 16) + (checksum & 0xffff);
	checksum = checksum + (checksum >> 16);
	return (~(unsigned short)checksum);
}

char	*hostname_to_ip(char *s)
{
	struct addrinfo		hints;
	struct addrinfo		*tmp;
	struct sockaddr_in	*addr;
	char				*res;

	ft_memset(&(hints), 0, sizeof(hints));
	hints.ai_family = AF_INET;
	res = malloc(INET_ADDRSTRLEN);
	if (!res)
		pexit("malloc");
	if (getaddrinfo(s, NULL, &hints, &(tmp)) < 0)
	{
		free(res);
		printf("ft_ping: %s: Name or service not known\n", s);
		exit(EXIT_FAILURE);
	}
	addr = (struct sockaddr_in *)tmp->ai_addr;
	inet_ntop(tmp->ai_family, &(addr->sin_addr), res, INET_ADDRSTRLEN);
	freeaddrinfo(tmp);
	return (res);
}
