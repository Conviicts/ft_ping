/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 12:28:18 by jode-vri          #+#    #+#             */
/*   Updated: 2022/12/12 13:11:08 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

t_bool	check_timeout(t_target *t)
{
	if (t->opts.need_timeout)
	{
		if (t->opts.verbose)
			printf("Request timeout for icmp_seq=%hu Time to live exceeded\n",
				t->conn.seq);
		alarm(0);
		t->opts.need_timeout = false;
		t->conn.seq++;
		return (true);
	}
	return (false);
}

void	wait_interval(int interval)
{
	struct timeval	current;
	struct timeval	next;

	if (gettimeofday(&current, NULL) < 0)
		pexit("gettimeofday");
	next = current;
	next.tv_sec += interval;
	while (current.tv_sec < next.tv_sec || current.tv_usec < next.tv_usec)
	{
		if (gettimeofday(&current, NULL) < 0)
			pexit("gettimeofday");
	}
}

t_bool	running(t_target *t)
{
	if (t->send_count == t->opts.limit && t->opts.limit != 0)
		return (false);
	return (true);
}

t_bool	receive_loop(t_target *t, struct timeval start_tv,
	struct timeval end_tv)
{
	int		count;
	double	duration;

	duration = 0;
	init_recv(t);
	count = recvmsg(t->conn.fd, &t->msg, MSG_DONTWAIT);
	if (gettimeofday(&end_tv, NULL) < 0)
		pexit("gettimeofday");
	if (check_timeout(t))
		return (false);
	if (t->icmp->icmp_hun.ih_idseq.icd_id == t->pid)
	{
		duration = (((double)end_tv.tv_sec * 1000000.0 + end_tv.tv_usec) - \
		((double)start_tv.tv_sec * 1000000.0 + start_tv.tv_usec)) / 1000;
		t->recv_count++;
		calculate_duration(t, duration);
		print_info(t, count, duration);
		wait_interval(t->opts.interval);
		alarm(0);
		t->opts.need_timeout = false;
		t->conn.seq++;
		return (false);
	}
	return (true);
}

void	loop(t_target *t)
{
	int				count;
	struct timeval	start_tv;
	struct timeval	end_tv;

	t->conn.seq = 1;
	t->send_count = 0;
	t->recv_count = 0;
	print_intro(t);
	while (running(t))
	{
		init_send(t, t->pid, t->conn.seq);
		if (gettimeofday(&start_tv, NULL) < 0)
			pexit("gettimeofday");
		count = sendto(t->conn.fd, t->buf,
				sizeof(t->buf), 0, t->conn.res->ai_addr,
				t->conn.res->ai_addrlen);
		if (count < 0)
			pexit("sendto");
		if (count >= 0)
			t->send_count++;
		alarm(t->opts.timeout);
		while (receive_loop(t, start_tv, end_tv))
			;
	}
	print_stats(t);
}
