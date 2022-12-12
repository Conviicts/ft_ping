/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 12:36:58 by jode-vri          #+#    #+#             */
/*   Updated: 2022/12/12 13:02:23 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

t_bool	handle_limit(t_opts *opts, char *value)
{
	if (check_value(value))
		return (false);
	opts->limit = ft_atoi(value);
	if (opts->limit <= 0 || opts->limit >= 9223372036854775807)
	{
		dprintf(STDERR_FILENO, "ping: invalid argument: '%s': out of range\n",
			value);
		return (false);
	}
	return (true);
}

t_bool	handle_ttl(t_opts *opts, char *value)
{
	if (check_value(value))
		return (false);
	opts->ttl = ft_atoi(value);
	if (opts->ttl <= 0)
	{
		perror("ft_ping: cannot set unicast time-to-live: Invalid argument");
		return (false);
	}
	if (opts->ttl > 255)
	{
		perror("ft_ping: invalid argument: out of range: 0 <= value <= 255");
		return (false);
	}
	return (true);
}

int	parse_option(t_opts *opts, char *option, char *value, int *i)
{
	int	j;

	j = -1;
	if (is_empty(option, option[j]))
		return (false);
	while (option[++j])
	{
		if (option[j] == 'c')
		{
			if (!handle_limit(opts, value))
				return (false);
			(*i)++;
		}
		else if (option[j] == 't')
		{
			if (!handle_ttl(opts, value))
				return (false);
			(*i)++;
		}
		else if (option[j] == 'v')
			opts->verbose = true;
		else
			print_help();
	}
	return (true);
}

int	parse_options(t_target *target, int ac, char **av)
{
	int		i;
	t_bool	have_hostname;

	have_hostname = 0;
	i = 0;
	while (++i < ac)
	{
		if (av[i][0] == '-')
		{
			if (!parse_option(&target->opts, av[i] + 1, av[i + 1], &i))
				return (false);
		}
		else
		{
			if (have_hostname)
				print_help();
			target->hostname = av[i];
			have_hostname = 1;
		}
	}
	if (!have_hostname)
		return (false);
	return (true);
}
