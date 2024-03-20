/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 08:21:14 by jode-vri          #+#    #+#             */
/*   Updated: 2024/03/20 08:51:53 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ping.h"

static bool	pare_option(t_options *opts, char *opt) {
	int j = 0;
	
	if (!opt[j]) {
		dprintf(STDERR_FILENO, "ft_ping: invalid option -- '-'\n");
		return (false);
	}
	while (opt[j]) {
		switch (opt[j]) {
			case 'v':
				opts->verbose = true;
				break;
			case 'h':
				opts->help = true;
				break;
			default:
				dprintf(STDERR_FILENO, "ft_ping: invalid option -- '%c'\n", opt[j]);
				return (false);
		}
		j++;
	}
	return (true);
}

bool	parse_options(t_ping *ping, int ac, char **av) {
	bool	have_hostname = false;
	int		i = 0;

	if (ac < 2)
		return (false);
	ft_bzero(&ping->options, sizeof(t_options));
	while (++i < ac) {
		if (av[i][0] == '-') {
			if (!pare_option(&ping->options, av[i] + 1))
				return (false);
		} else {
			if (have_hostname)
				continue;
			ping->dest.hostname = av[i];
			have_hostname = true;
		}
	}
	if (!have_hostname)
		return (false);
	return (true);
}