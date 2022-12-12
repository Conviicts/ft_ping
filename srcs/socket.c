/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 12:25:50 by jode-vri          #+#    #+#             */
/*   Updated: 2022/12/12 12:48:56 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	init_send(t_target *t, USHORT id, USHORT seq)
{
	ft_memset(&(t->buf), 0, sizeof(t->buf));
	t->ip->ip_v = 4;
	t->ip->ip_hl = sizeof(*(t->ip)) >> 2;
	t->ip->ip_tos = 0;
	t->ip->ip_len = htons(sizeof(t->buf));
	t->ip->ip_id = 0;
	t->ip->ip_off |= 0;
	t->ip->ip_ttl = t->opts.ttl;
	t->ip->ip_p = t->conn.res->ai_protocol;
	t->ip->ip_sum = 0;
	inet_pton(t->conn.res->ai_family, t->source, &(t->ip->ip_src.s_addr));
	inet_pton(t->conn.res->ai_family, t->destination, &(t->ip->ip_dst.s_addr));
	t->icmp->icmp_type = ICMP_ECHO;
	t->icmp->icmp_code = 0;
	t->icmp->icmp_hun.ih_idseq.icd_id = id;
	t->icmp->icmp_hun.ih_idseq.icd_seq = seq;
	t->icmp->icmp_cksum = icmp_checksum((unsigned short *)t->icmp,
			sizeof(t->icmp));
}

void	init_recv(t_target *t)
{
	ft_memset(&(t->buf), 0, sizeof(t->buf));
	t->iov[0].iov_base = t->buf;
	t->iov[0].iov_len = sizeof(t->buf);
	t->msg.msg_name = t->conn.res->ai_addr;
	t->msg.msg_namelen = t->conn.res->ai_addrlen;
	t->msg.msg_iov = t->iov;
	t->msg.msg_iovlen = 1;
	t->msg.msg_control = &(t->buf_control);
	t->msg.msg_controllen = sizeof(t->buf_control);
	t->msg.msg_flags = 0;
}

void	connect_socket(t_target *t)
{
	int	opt;

	opt = 1;
	ft_memset(&t->conn.hints, 0, sizeof(t->conn.hints));
	t->conn.hints.ai_family = AF_INET;
	t->conn.hints.ai_socktype = SOCK_RAW;
	t->conn.hints.ai_protocol = IPPROTO_ICMP;
	if (getaddrinfo(t->hostname, NULL, &t->conn.hints,
			&t->conn.res) < 0)
		pexit("ft_ping: unknown host");
	t->conn.fd = socket(t->conn.res->ai_family,
			t->conn.res->ai_socktype, t->conn.res->ai_protocol);
	if (t->conn.fd < 0)
		pexit("ft_ping: unable to open socket.");
	if (setsockopt(t->conn.fd, IPPROTO_IP, IP_HDRINCL, &opt,
			sizeof(opt)) < 0)
		pexit("ft_ping: unable to set socket options.");
}
