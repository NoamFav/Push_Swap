/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort_3way.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfavier <noam.favier@learner.42.tech>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 22:25:33 by nfavier           #+#    #+#             */
/*   Updated: 2026/11/19 00:21:51 by nfavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

bool	sort_a(t_ctx *ctx, size_t low, size_t high)
{
	int			mid;
	size_t		count;
	int			k;
	t_ops		op;

	count = 0;
	k = high - low + 1;
	if (k <= 3)
		return (sort_small_a(ctx, k));
	mid = (low + high) / 2;
	while (k--)
	{
		op = RA;
		if (stack_get(&ctx->a, 0) < mid)
			op = PB;
		count += (op == RA);
		if (!do_op(ctx, op))
			return (false);
	}
	if (!rotate_back(ctx, &ctx->a, count, RRA))
		return (false);
	return (sort_a(ctx, mid, high) && sort_b(ctx, low, mid - 1));
}

bool	sort_b(t_ctx *ctx, size_t low, size_t high)
{
	int			mid;
	size_t		count;
	int			k;
	t_ops		op;

	count = 0;
	k = high - low + 1;
	if (k <= 3)
		return (sort_small_b(ctx, k));
	mid = (low + high) / 2;
	while (k--)
	{
		op = RB;
		if (stack_get(&ctx->b, 0) >= mid)
			op = PA;
		count += (op == RB);
		if (!do_op(ctx, op))
			return (false);
	}
	if (!rotate_back(ctx, &ctx->b, count, RRB))
		return (false);
	return (sort_a(ctx, mid, high) && sort_b(ctx, low, mid - 1));
}

bool	quick_sort(t_ctx *ctx)
{
	if (stack_is_sorted(&ctx->a))
		return (true);
	return (sort_a(ctx, 0, ctx->a.cap - 1));
}
