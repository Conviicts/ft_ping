/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 07:42:46 by jode-vri          #+#    #+#             */
/*   Updated: 2024/03/20 09:38:12 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ping.h"

void	init_packet(t_packet *packet, time_t time) {
	ft_bzero(packet, sizeof(t_packet));
	
	packet->icmp.icmp_type = ICMP_ECHO;
	packet->icmp.icmp_code = 0;
	packet->icmp.icmp_id = getpid();
	g_ping->stats.transmitted++;
	packet->icmp.icmp_seq = g_ping->stats.transmitted;
	packet->time = time;
	ft_memcpy(&packet->icmp.icmp_dun, &time, sizeof(time));
	//TODO: packet checksum
}

void	loop(t_ping *ping) {
	(void)ping;
	t_packet		packet;
	struct timeval	tv_start;
	bool			need_send = true;

	printf("PING %s (%s): %d data bytes\n", ping->dest.hostname, ping->dest.ip, PACKET_SIZE);
	ping->fd = init_socket();
	if (gettimeofday((struct timeval *)&ping->stats.tv_start, NULL) == -1){
		perror("gettimeofday");
		//TODO: exit properly
		exit(EXIT_FAILURE);
	}
	while (true) {
		if (need_send) {
			if (gettimeofday(&tv_start, NULL) == -1) {
				perror("gettimeofday");
				//TODO: exit properly
				exit(EXIT_FAILURE);
			}
			init_packet(&packet, tv_start.tv_sec);
			if (ping->options.interval > 0) {
				ping->wait = true;
				alarm(ping->options.interval);
			}
			printf("%d %p %d\n", ping->fd, ping->dest.res->ai_addr, ping->dest.res->ai_addrlen);
			printf("%p %ld\n", &packet, sizeof(packet));
			if (sendto(ping->fd, &packet, sizeof(packet), 0, (struct sockaddr *)ping->dest.res->ai_addr, ping->dest.res->ai_addrlen) == -1) {
				// perror("sendto");
				printf("sendto: %s\n", strerror(errno));
				//TODO: exit properly
				exit(EXIT_FAILURE);
			}
		}
		printf("pd\n");
		struct msghdr msg;
		int read_bytes = recvmsg(ping->fd, &msg, 0);
		printf("read_bytes: %d\n", read_bytes);
		
		while (ping->options.interval > 0 && ping->wait);
	}
}