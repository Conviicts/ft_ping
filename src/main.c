/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 06:03:17 by jode-vri          #+#    #+#             */
/*   Updated: 2024/02/19 06:28:41 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ping.h"

int main(int ac, char **av) {
	(void)av;
	if (ac == 1) {
		printf("ft_ping: missing host operand\n");
		printf("Try 'ft_ping --help' or 'ft_ping --usage' for more information.\n");
		return (64);
	}
	if (getuid() != 0) {
		printf("ft_ping: Lacking privilege for icmp socket.\n");
		return (1);
	}
}