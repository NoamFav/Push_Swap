/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre.janssen@learner.42.tech          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 09:34:17 by ajanssen          #+#    #+#             */
/*   Updated: 2026/11/19 11:14:16 by ajanssen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

static size_t	find_min(const t_stack *s)
{
	size_t	i;
	size_t	min_idx;

	min_idx = 0;
	i = 0;
	while (++i < s->curr_size)
	{
		if (stack_get(s, i) < stack_get(s, min_idx))
			min_idx = i;
	}
	return (min_idx);
}

/* choose the least costly direction to bring the min to the top */
static bool	bring_to_top(t_ctx *ctx, size_t pos)
{
	size_t	count;
	t_ops	op;

	op = RA;
	count = pos;
	if (pos > ctx->a.curr_size / 2)
	{
		op = RRA;
		count = ctx->a.curr_size - pos;
	}
	while (count--)
	{
		if (!do_op(ctx, op))
			return (false);
	}
	return (true);
}

/*
** Selection sort, time complexity O(n²)
** We repeatedly take the min in stack a and push it to b
** then push everything back to a to get an ascending order.
** Early stop if a is sorted: we just push b on top.
*/
bool	sort_selection(t_ctx *ctx)
{
	while (!stack_is_sorted(&ctx->a))
	{
		if (!bring_to_top(ctx, find_min(&ctx->a)) || !do_op(ctx, PB))
			return (false);
	}
	while (ctx->b.curr_size > 0)
	{
		if (!do_op(ctx, PA))
			return (false);
	}
	return (true);
}
