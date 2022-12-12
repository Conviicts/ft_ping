/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 12:30:05 by jode-vri          #+#    #+#             */
/*   Updated: 2022/12/12 13:15:24 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	sigint_handler(__attribute__((unused))int c)
{
	printf("\n");
	print_stats(g_t);
	exit(EXIT_SUCCESS);
}

void	sigalrm_handler(__attribute__((unused))int c)
{
	g_t->opts.need_timeout = true;
}
