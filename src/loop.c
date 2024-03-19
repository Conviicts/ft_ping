/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 07:42:46 by jode-vri          #+#    #+#             */
/*   Updated: 2024/03/10 08:02:15 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ping.h"

void    loop(t_ping *ping) {
    bool            send = true;
	struct timeval  tv_start;

	printf("PING %s (%s): 56 data bytes\n", g_ping->dest.hostname, g_ping->dest.destination);
    if (gettimeofday((struct timeval *)&ping->stats.tv_start, NULL) == -1) {
        //TODO: handle error
    }
    while (true) {
        if (send) {
			if (gettimeofday(&tv_start, NULL) == -1) {
                //TODO: handle error
            }
            //TODO: construct packet
            if (ping->options.interval > 0) {
                ping->wait = true;
                printf("alrm\n");
                alarm(ping->options.interval);
            }
            //TODO: send packet
        }
        //TODO: construct packet
        //TODO: recv packet
        

        if (gettimeofday((struct timeval *)&ping->stats.tv_end, NULL) == -1) {
            //TODO: handle error
        }
    }
    
}