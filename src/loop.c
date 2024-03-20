/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 07:42:46 by jode-vri          #+#    #+#             */
/*   Updated: 2024/03/20 09:54:39 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ping.h"

uint16_t	checksum(void *addr, int size) {
	uint16_t	*buff;
	uint32_t	sum;

	buff = (uint16_t *)addr;
	for (sum = 0; size > 1; size -= 2)
		sum += *buff++;
	if (size == 1)
		sum += *(uint8_t*)buff;
	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
	return (~sum);
}

void	init_packet(t_packet *packet, time_t time) {
	ft_bzero(packet, sizeof(t_packet));
	
	packet->icmp.icmp_type = ICMP_ECHO;
	packet->icmp.icmp_code = 0;
	packet->icmp.icmp_id = getpid();
	g_ping->stats.transmitted++;
	packet->icmp.icmp_seq = g_ping->stats.transmitted;
	packet->icmp.icmp_cksum = checksum(packet, sizeof(*packet));
	packet->timestamp = time;
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
            char buffer[56];
            ft_bzero(&buffer, sizeof(buffer));
			if (sendto(ping->fd, &buffer, sizeof(buffer), 0, (struct sockaddr *)ping->dest.res->ai_addr, ping->dest.res->ai_addrlen) == -1) {
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