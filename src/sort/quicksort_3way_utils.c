/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort_3way_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfavier <noam.favier@learner.42.tech>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 00:19:43 by nfavier           #+#    #+#             */
/*   Updated: 2026/11/19 00:20:04 by nfavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

bool	sort_small_a(t_ctx *ctx, int k)
{
	if (k >= 2 && stack_get(&ctx->a, 0) > stack_get(&ctx->a, 1))
		if (!do_op(ctx, SA))
			return (false);
	if (k == 3)
	{
		if (stack_get(&ctx->a, 1) > stack_get(&ctx->a, 2))
			if (!(do_op(ctx, PB) && do_op(ctx, SA) && do_op(ctx, PA)))
				return (false);
		if (stack_get(&ctx->a, 0) > stack_get(&ctx->a, 1))
			if (!do_op(ctx, SA))
				return (false);
	}
	return (true);
}

bool	sort_small_b(t_ctx *ctx, int k)
{
	int	count;

	count = k;
	while (count--)
		if (!do_op(ctx, PA))
			return (false);
	return (sort_small_a(ctx, k));
}

bool	rotate_back(t_ctx *ctx, t_stack *s, size_t count, t_ops op)
{
	if (s->curr_size > count)
		while (count-- != 0)
			if (!do_op(ctx, op))
				return (false);
	return (true);
}
