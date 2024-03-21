/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 06:03:17 by jode-vri          #+#    #+#             */
/*   Updated: 2024/03/21 08:03:26 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ping.h"

struct s_ping	*g_ping;

void	print_help(void) {
	printf("Try 'ping --help' or 'ping --usage' for more information.\n");
	exit(0);
}

void	get_ip(t_ping *ping) {
	struct addrinfo	hints;
	
	ft_memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	if (getaddrinfo(ping->dest.hostname, NULL, &hints, &ping->dest.res) == -1) {
		dprintf(STDERR_FILENO, "ft_ping: %s: Name or service not known\n", ping->dest.hostname);
		//TODO: exit properly
		exit(EXIT_FAILURE);
	}
	ft_memcpy(&(ping->dest.sa_in), (void *)ping->dest.res->ai_addr, sizeof(struct sockaddr_in));
	inet_ntop(ping->dest.res->ai_family, &(ping->dest.sa_in.sin_addr), ping->dest.ip, INET_ADDRSTRLEN);
}

void	init_ping(t_ping *ping) {
	g_ping = ping;
	ft_bzero(&ping->stats, sizeof(t_stats));
	if (!ping->options.interval)
		ping->options.interval = 1;
	if (!ping->options.ttl)
		ping->options.ttl = 64;
	ping->fd = -1;
	ping->wait = false;
	ping->running = true;
	get_ip(ping);
}

int		main(int ac, char **av) {
	t_ping	ping;

	ft_bzero(&ping, sizeof(t_ping));
	if (!parse_options(&ping, ac, av)) {
		print_help();
		return(EXIT_FAILURE);
	}
	init_ping(&ping);
	signal(SIGINT, &signal_handler);
	signal(SIGALRM, &signal_handler);
	loop(&ping);
}