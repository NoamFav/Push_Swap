/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfavier <noam.favier@learner.42.tech>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 20:19:18 by nfavier           #+#    #+#             */
/*   Updated: 2026/11/18 15:50:35 by nfavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "utils.h"

static const char	*op_name(t_ops op)
{
	static const char *const	table[OP_COUNT] = {
		"sa", "sb", "ss",
		"pa", "pb",
		"ra", "rb", "rr",
		"rra", "rrb", "rrr",
	};

	return (table[op]);
}

static t_ops	merge(t_ops a, t_ops b)
{
	if ((a == SA && b == SB) || (a == SB && b == SA))
		return (SS);
	if ((a == RA && b == RB) || (a == RB && b == RA))
		return (RR);
	if ((a == RRA && b == RRB) || (a == RRB && b == RRA))
		return (RRR);
	return (OP_COUNT);
}

static bool	cancels(t_ops a, t_ops b)
{
	return ((a == PA && b == PB) || (a == PB && b == PA)
		|| (a == RA && b == RRA) || (a == RRA && b == RA)
		|| (a == RB && b == RRB) || (a == RRB && b == RB)
		|| (a == RRR && b == RR) || (a == RR && b == RRR)
		|| (a == SA && b == SA)
		|| (a == SB && b == SB)
		|| (a == SS && b == SS));
}

bool	ops_flush(t_ctx *ctx)
{
	t_opbuf		*ops;
	const char	*name;
	size_t		i;

	i = (size_t)-1;
	ops = &ctx->ops;
	while (++i < ops->len)
	{
		name = op_name(((t_ops){ops->data[i]}));
		if (ft_dprintf(1, "%s\n", name) == -1)
			return (false);
	}
	return (true);
}

bool	ops_clean(t_ctx *ctx)
{
	size_t	i;
	size_t	w;
	t_ops	merged;

	w = 0;
	i = (size_t) - 1;
	while (++i < ctx->ops.len)
	{
		merged = OP_COUNT;
		if (w > 0)
			merged = merge(ctx->ops.data[w - 1], ctx->ops.data[i]);
		if (w > 0 && cancels(ctx->ops.data[w - 1], ctx->ops.data[i]))
			w--;
		else if (merged != OP_COUNT)
			ctx->ops.data[w - 1] = merged;
		else
			ctx->ops.data[w++] = ctx->ops.data[i];
	}
	ctx->ops.len = w;
	i = (size_t) - 1;
	while (++i < OP_COUNT)
		ctx->counts[i] = 0;
	while (w--)
		ctx->counts[ctx->ops.data[w]]++;
	return (true);
}
