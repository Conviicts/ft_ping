/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 07:42:46 by jode-vri          #+#    #+#             */
/*   Updated: 2024/03/21 08:14:26 by jode-vri         ###   ########.fr       */
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
	packet->icmp.icmp_id = (uint16_t)getpid();
	g_ping->stats.transmitted++;
	packet->icmp.icmp_seq = g_ping->stats.transmitted;
	packet->timestamp = time;
	ft_memcpy(&packet->icmp.icmp_dun, &time, sizeof(time));
	packet->icmp.icmp_cksum = checksum(packet, sizeof(*packet));
}

void	init_receive_packet(t_response *response) {
	ft_bzero(response, sizeof(t_response));
	response->msg.msg_name = NULL;
	response->msg.msg_iov = &response->iov;
	response->iov.iov_base = response->recv_buff;
	response->iov.iov_len = sizeof(response->recv_buff);
	response->msg.msg_iovlen = 1;
	response->msg.msg_control = &response->ctrl;
	response->msg.msg_controllen = sizeof(response->ctrl);
}

void	loop(t_ping *ping) {
	t_packet		packet;
	t_response		response;
	struct timeval	tv_start;
	int				sequence = 0;
	bool			need_send = true;

	printf("PING %s (%s): %d data bytes\n", ping->dest.hostname, ping->dest.ip, PACKET_SIZE);
	ping->fd = init_socket();
	if (gettimeofday((struct timeval *)&ping->stats.tv_start, NULL) == -1){
		perror("gettimeofday");
		//TODO: exit properly
		exit(EXIT_FAILURE);
	}
	while (ping->running) {
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
			if (sendto(ping->fd, &packet, sizeof(packet), 0, (struct sockaddr *)&ping->dest.sa_in, sizeof(ping->dest.sa_in)) == -1) {
				// perror("sendto");
				printf("sendto: %s\n", strerror(errno));
				//TODO: exit properly
				exit(EXIT_FAILURE);
			}
		}

		init_receive_packet(&response);
		int read_bytes = recvmsg(ping->fd, &response.msg, 0);
		if (read_bytes == 0) {
			dprintf(STDERR_FILENO, "ft_ping: socket closed\n");
			//TODO: exit properly
			exit(EXIT_FAILURE);
		} else if (read_bytes == -1) {
			if (errno == EINTR || errno == EAGAIN) {
				need_send = true;
				if (ping->options.verbose)
					printf("Request timeout for icmp_seq %d\n", g_ping->stats.transmitted);
			} else {
				perror("recvmsg");
			}
		} else {
			print_stat(ping, &tv_start, sequence);
		}
		if (gettimeofday(&ping->stats.tv_end, NULL) == -1) {
			printf("gettimeofday error\n");
			//TODO: exit properly
			exit(EXIT_FAILURE);
		}
		sequence++;
		
		while (ping->options.interval > 0 && ping->wait && ping->running);
	}
	print_stats(ping);
}