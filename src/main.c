/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 06:03:17 by jode-vri          #+#    #+#             */
/*   Updated: 2024/03/02 20:45:50 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ping.h"

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
	ft_bzero(&ping, sizeof(t_ping));
	pos = parse_options(&ping, ac, av);
	ping.options.interval = 1;
	ping.options.timeout = 1;
	ping.options.ttl = 64;
	ping.hostname = av[pos];
	ping.destination = get_hostname(ping.hostname);
	ping.pid = getpid();
	if (!init_socket(&ping))
		return (1);
}