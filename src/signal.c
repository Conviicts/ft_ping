/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 07:10:52 by jode-vri          #+#    #+#             */
/*   Updated: 2024/03/21 08:03:47 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ping.h"

void    signal_handler(int sig) {
	(void)sig;
	if (sig == SIGINT) {
		g_ping->running = false;
	} else if (sig == SIGALRM) {
		g_ping->wait = false;	
	}
}