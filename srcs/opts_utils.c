/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opts_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 12:54:47 by jode-vri          #+#    #+#             */
/*   Updated: 2022/12/12 12:56:00 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

t_bool	check_value(char *v)
{
	if (!v)
	{
		print_help();
		return (true);
	}
	return (false);
}

t_bool	is_empty(char *option, char c)
{
	if (option[0] == '\0')
	{
		dprintf(STDERR_FILENO,
			"ft_ping: %c: Temporary failure in name resolution\n", c);
		return (true);
	}
	return (false);
}
