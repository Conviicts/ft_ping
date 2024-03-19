/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 06:03:17 by jode-vri          #+#    #+#             */
/*   Updated: 2024/03/10 08:02:42 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ping.h"

struct s_ping	*g_ping;

void	print_help(void) {
	printf("Try 'ping --help' or 'ping --usage' for more information.\n");
	exit(0);
}

int		parse_options(t_ping *ping, int ac, char **av) {
	int opt;

	while ((opt = getopt(ac, av, "vh")) != -1) {
		switch (opt) {
			case 'v':
				ping->options.verbose = true;
				break;
			case 'h':
				ping->options.help = true;
				break;
			default:
				print_help();
		}
	}
	return (optind);
}

static void	init(t_ping *ping, char **av, int pos) {
	g_ping = ping;
	ping->options.ttl = 64;
	ping->options.interval = 1;
	ping->dest.hostname = av[pos];
	ping->dest.destination = get_hostname(ping->dest.hostname);
	ping->pid = getpid();
	ping->wait = false;
	ft_bzero(&ping->stats, sizeof(t_stats));
}

int		main(int ac, char **av) {
	t_ping	ping;
	int		pos;

	if (ac == 1) {
		printf("ft_ping: missing host operand\n");
		printf("Try 'ft_ping --help' or 'ft_ping --usage' for more information.\n");
		return (64);
	}
	if (getuid() != 0) {
		printf("ft_ping: Lacking privilege for icmp socket.\n");
		return (1);
	}
	pos = parse_options(&ping, ac, av);
	init(&ping, av, pos);
	signal(SIGINT, &signal_handler);
	signal(SIGALRM, &signal_handler);
	loop(&ping);
	free(ping.dest.destination);
}