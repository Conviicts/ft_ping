/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 12:24:15 by jode-vri          #+#    #+#             */
/*   Updated: 2022/12/12 13:31:17 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	print_help(void)
{
	printf("Usage\n  ping [options] <destination>\n\n");
	printf("Options:\n");
	printf("  <destination>      dns name or ip address\n");
	printf("  -h                 print help and exit\n");
	printf("  -v                 verbose output\n\n");
	printf("IPv4 Options:\n");
	printf("  -4                 use IPv4\n\n");
	printf("IPv6 Options:\n");
	printf("  -6                 use IPv6\n\n");
	exit(EXIT_SUCCESS);
}

void	print_intro(t_target *t)
{
	printf("PING %s (%s) %ld(84) bytes of data.\n", t->hostname, t->destination,
		sizeof(t->buf) - sizeof(*(t->icmp)));
}

void	print_info(t_target *t, int length, double duration)
{
	printf("%lu bytes from %s: icmp_seq=%d ttl=%d time=%.3lf ms\n",
		length - sizeof(*(t->ip)), t->destination, t->conn.seq,
		t->ip->ip_ttl, duration);
}

void	print_stats(t_target *t)
{
	double	lost;
	double	avg;
	double	total;

	lost = 0;
	avg = 0;
	total = 0;
	if (t->send_count != 0)
		lost = 100 - ((t->recv_count * 100) / t->send_count);
	printf("-- %s ping statistics ---\n", t->hostname);
	printf("%lu packets transmitted, %u packets received, %.2f%% packet loss\n",
		t->send_count, t->recv_count, lost);
	if (t->send_count != 0)
		avg = t->conn.total / t->send_count;
	if ((t->send_count - avg * avg) != 0)
		total = t->conn.ratio / t->send_count - avg * avg;
	if (t->recv_count > 0)
		printf("rtt min/avg/max/mdev = %.3f/%.3f/%.3f/%.3f ms\n",
			t->conn.duration_min, avg, t->conn.duration_max, sqrt(total));
	freeaddrinfo(t->conn.res);
	free(t->destination);
	exit(0);
}
