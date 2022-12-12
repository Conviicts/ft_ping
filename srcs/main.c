/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 04:05:52 by jode-vri          #+#    #+#             */
/*   Updated: 2022/12/12 13:13:51 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	pexit(char *s)
{
	printf("%s\n", s);
	exit(EXIT_FAILURE);
}

int	main(int ac, char **av)
{
	t_target	target;

	if (ac < 2)
		pexit("ft_ping: usage error: Destination address required");
	if (getuid() != 0)
		pexit("ft_ping: Operation not permited");
	g_t = &target;
	ft_bzero(&target, sizeof(target));
	ft_bzero(&target.opts, sizeof(target.opts));
	target.opts.limit = 0;
	target.opts.interval = 1;
	target.opts.timeout = 4;
	target.opts.ttl = 64;
	if (!parse_options(&target, ac, av))
		exit(EXIT_FAILURE);
	target.conn.duration_min = DBL_MAX;
	target.pid = getpid();
	target.destination = hostname_to_ip(target.hostname);
	target.source = "0.0.0.0";
	connect_socket(&target);
	target.ip = (struct ip *)target.buf;
	target.icmp = (struct icmp *)(target.ip + 1);
	signal(SIGALRM, &sigalrm_handler);
	signal(SIGINT, &sigint_handler);
	loop(&target);
}
