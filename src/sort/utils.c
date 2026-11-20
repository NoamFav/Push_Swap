/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfavier <noam.favier@learner.42.tech>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 14:50:10 by nfavier           #+#    #+#             */
/*   Updated: 2026/11/20 16:16:15 by nfavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

/* a[i] > a[j], exists purely so the lines below fit in 80 cols */
static bool	gt(t_ctx *ctx, size_t i, size_t j)
{
	return (stack_get(&ctx->a, i) > stack_get(&ctx->a, j));
}

/*
** top k (<= 3) of a. alone: rotations are free, max to the bottom first.
** stuff below: no rotating, the sorted part would come along for the ride.
** "rule && !do_op": the op only runs if the rule holds
*/
bool	sort_small_a(t_ctx *ctx, int k)
{
	if (k == 3 && ctx->a.curr_size == 3)
	{
		if (gt(ctx, 0, 1) && gt(ctx, 0, 2) && !do_op(ctx, RA))
			return (false);
		if (gt(ctx, 1, 2) && !do_op(ctx, RRA))
			return (false);
	}
	if (k >= 2 && gt(ctx, 0, 1) && !do_op(ctx, SA))
		return (false);
	if (k == 3)
	{
		if (gt(ctx, 1, 2)
			&& !(do_op(ctx, PB) && do_op(ctx, SA) && do_op(ctx, PA)))
			return (false);
		if (gt(ctx, 0, 1) && !do_op(ctx, SA))
			return (false);
	}
	return (true);
}

/* lazy on purpose: dump it on a, sort it there */
bool	sort_small_b(t_ctx *ctx, int k)
{
	int	count;

	count = k;
	while (count--)
		if (!do_op(ctx, PA))
			return (false);
	return (sort_small_a(ctx, k));
}

/* brings parked elements back up. skipped if they're the whole stack */
bool	rotate_back(t_ctx *ctx, t_stack *s, size_t count, t_ops op)
{
	if (s->curr_size > count)
		while (count-- != 0)
			if (!do_op(ctx, op))
				return (false);
	return (true);
}
