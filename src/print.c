/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 08:09:41 by jode-vri          #+#    #+#             */
/*   Updated: 2024/03/21 08:25:41 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ping.h"

void	update_stats(double diff) {
	if (g_ping->stats.received == 1) {
		g_ping->stats.rt_min = diff;
	} else {
		if (g_ping->stats.rt_min > diff)
			g_ping->stats.rt_min = diff;
	}
	if (g_ping->stats.rt_max < diff)
		g_ping->stats.rt_max = diff;
	g_ping->stats.rt_avg += diff;
	g_ping->stats.rt_stddev += diff * diff;
}

void	print_stat(t_ping *ping, struct timeval *tv_start, int sequence) {
	struct timeval	tv_diff;
	
	ping->stats.received++;
	if (gettimeofday(&tv_diff, NULL) == -1) {
		perror("gettimeofday");
		//TODO: exit properly
		exit(EXIT_FAILURE);
	}
	double diff = (double)(tv_diff.tv_sec - tv_start->tv_sec) * 1000.0 + (double)(tv_diff.tv_usec - tv_start->tv_usec) / 1000.0;
	printf("%d bytes from %s: icmp_seq=%hu ttl=%d time=%.3lf ms\n", PACKET_SIZE, ping->dest.ip, sequence, ping->options.ttl, diff);
	update_stats(diff);
}

void	print_stats(t_ping *ping) {
	// struct timeval	tv_diff;
	double			total;
	double			avg;
	// double			stddev;
	
	if (ping->stats.received == 0)
		return ;
		
	ping->stats.transmitted == 1 ? total = 0.0 : (total = (double)(ping->stats.tv_end.tv_sec - ping->stats.tv_start.tv_sec) * 1000.0 + (double)(ping->stats.tv_end.tv_usec - ping->stats.tv_start.tv_usec) / 1000.0);
	printf("--- %s ping statistics ---\n", ping->dest.hostname);
	if (ping->stats.transmitted == ping->stats.received) {
		printf("%d packets transmitted, %d received, 0%% packet loss\n", ping->stats.transmitted, ping->stats.received);
		avg = ping->stats.rt_avg / ping->stats.received;
		printf("round-trip min/avg/max/stddev = %.3lf/%.3lf/%.3lf/%.3lf ms\n", ping->stats.rt_min, avg, ping->stats.rt_max, 0.0);
		
	} else {
		printf("%d packets transmitted, %d received, %d%% packet loss\n", ping->stats.transmitted, ping->stats.received, (ping->stats.transmitted - ping->stats.received) * 100 / ping->stats.transmitted);
	}
		
	
}