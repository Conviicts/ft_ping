/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 07:10:52 by jode-vri          #+#    #+#             */
/*   Updated: 2024/03/10 08:01:21 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ping.h"

void    ping_exit() {
    if (g_ping->dest.destination)
        free(g_ping->dest.destination);
    exit(EXIT_SUCCESS);
}

void    signal_handler(int sig) {
    if (sig == SIGINT) {
        //TODO: display stats
        ping_exit();
    } else if (sig == SIGALRM) {
        g_ping->wait = true;
    }
}