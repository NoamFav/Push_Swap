/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ksort.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre.janssen@learner.42.tech          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 20:59:50 by ajanssen          #+#    #+#             */
/*   Updated: 2026/11/20 15:19:14 by nfavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

static size_t	floor_sqrt(size_t n)
{
	size_t	r;

	r = 1;
	while (r * r <= n)
		r++;
	return (r - 1);
}

static size_t	max_pos(const t_stack *s)
{
	size_t	i;
	size_t	max_idx;

	max_idx = 0;
	i = 1;
	while (i < s->curr_size)
	{
		if (stack_get(s, i) > stack_get(s, max_idx))
			max_idx = i;
		i++;
	}
	return (max_idx);
}

/*
** fill B with a sliding window of width k to find the low values first
**   rank <= i      overdue: PB, then RB to put it at the bottom of B
**   rank <= i + k  in the window: PB on top of B
**   otherwise      too early: skip it with RA
*/
static bool	push_chunked(t_ctx *ctx, size_t k)
{
	size_t	i;
	size_t	top;

	i = 0;
	while (ctx->a.curr_size > 0)
	{
		top = (size_t)stack_get(&ctx->a, 0);
		if (top <= i + k)
		{
			if (!do_op(ctx, PB))
				return (false);
			if (top <= i && ctx->b.curr_size > 1 && !do_op(ctx, RB))
				return (false);
			i++;
		}
		else if (!do_op(ctx, RA))
			return (false);
	}
	return (true);
}

/* "selection sort like" pull, using the fuzzily ordered stack B */
static bool	pull_back(t_ctx *ctx)
{
	size_t	pos;
	size_t	steps;
	t_ops	op;

	while (ctx->b.curr_size > 0)
	{
		pos = max_pos(&ctx->b);
		op = RB;
		steps = pos;
		if (pos > ctx->b.curr_size / 2)
		{
			op = RRB;
			steps = ctx->b.curr_size - pos;
		}
		while (steps > 0)
		{
			if (!do_op(ctx, op))
				return (false);
			steps--;
		}
		if (!do_op(ctx, PA))
			return (false);
	}
	return (true);
}

/* KSORT_SQRT_FACTOR=2 to tweak */
bool	sort_k(t_ctx *ctx)
{
	if (stack_is_sorted(&ctx->a))
		return (true);
	if (!push_chunked(ctx, floor_sqrt(KSORT_SQRT_FACTOR * ctx->a.curr_size)))
		return (false);
	return (pull_back(ctx));
}
