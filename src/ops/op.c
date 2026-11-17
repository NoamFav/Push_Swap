/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfavier <noam.favier@learner.42.tech>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 15:56:51 by nfavier           #+#    #+#             */
/*   Updated: 2026/11/17 16:04:35 by nfavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ops.h"

static bool	expand_buff(t_opbuf *buf)
{
	unsigned char	*tmp;
	size_t			size;
	size_t			new_cap;
	size_t			i;

	i = (size_t)-1;
	size = buf->len;
	new_cap = buf->cap + ((buf->cap + 1) / 2);
	tmp = malloc(sizeof(unsigned char) * new_cap);
	if (!tmp)
		return (false);
	buf->cap = new_cap;
	while (++i < size)
		tmp[i] = buf->data[i];
	free(buf->data);
	buf->data = tmp;
	return (true);
}

bool	opbuf_init(t_opbuf *buf, size_t n)
{
	if (n == 0)
		n = 16;
	buf->data = malloc(sizeof(unsigned char) * n);
	if (!buf->data)
		return (false);
	buf->len = 0;
	buf->cap = n;
	return (true);
}

bool	opbuf_push(t_opbuf *buf, t_ops op)
{
	if (buf->len == buf->cap && !expand_buff(buf))
		return (false);
	buf->data[buf->len] = op;
	buf->len++;
	return (true);
}

void	opbuf_free(t_opbuf *buf)
{
	free(buf->data);
	*buf = (t_opbuf){NULL, 0, 0};
}

bool	do_op(t_ctx *ctx, t_ops op)
{
	static const t_opfn	table[OP_COUNT] = {
		swap_a, swap_b, swap_both,
		push_a, push_b,
		rotate_a, rotate_b, rotate_both,
		rrotate_a, rrotate_b, rrotate_both,
	};

	if (!opbuf_push(&ctx->ops, op))
		return (false);
	ctx->counts[op]++;
	table[op](ctx);
	return (true);
}
