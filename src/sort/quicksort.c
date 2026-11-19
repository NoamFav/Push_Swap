/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfavier <noam.favier@learner.42.tech>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 22:25:33 by nfavier           #+#    #+#             */
/*   Updated: 2026/11/19 15:02:14 by nfavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

bool	partition_a(t_ctx *ctx, t_quicksort *qs)
{
	while (qs->k--)
	{
		qs->op = RA;
		if (stack_get(&ctx->a, 0) < qs->p[0])
		{
			qs->op = RB;
			if (!do_op(ctx, PB))
				return (false);
		}
		else if (stack_get(&ctx->a, 0) < qs->p[1])
			qs->op = PB;
		qs->count[0] += (qs->op == RA);
		qs->count[1] += (qs->op == RB);
		if (!do_op(ctx, qs->op))
			return (false);
	}
	return (true);
}

bool	partition_b(t_ctx *ctx, t_quicksort *qs)
{
	while (qs->k--)
	{
		qs->op = PA;
		if (stack_get(&ctx->b, 0) < qs->p[0])
			qs->op = RB;
		else if (stack_get(&ctx->b, 0) < qs->p[1])
		{
			qs->op = RA;
			if (!do_op(ctx, PA))
				return (false);
		}
		qs->count[0] += (qs->op == RA);
		qs->count[1] += (qs->op == RB);
		if (!do_op(ctx, qs->op))
			return (false);
	}
	return (true);
}

bool	sort_a(t_ctx *ctx, size_t low, size_t high)
{
	t_quicksort	qs;

	qs = (t_quicksort){0};
	qs.k = high - low + 1;
	if (qs.k <= 3)
		return (sort_small_a(ctx, qs.k));
	qs.p[0] = low + qs.k / 3;
	qs.p[1] = low + 2 * qs.k / 3;
	if (!partition_a(ctx, &qs))
		return (false);
	return (rotate_back(ctx, &ctx->a, qs.count[0], RRA)
		&& sort_a(ctx, qs.p[1], high)
		&& sort_b(ctx, qs.p[0], qs.p[1] - 1)
		&& rotate_back(ctx, &ctx->b, qs.count[1], RRB)
		&& sort_b(ctx, low, qs.p[0] - 1));
}

bool	sort_b(t_ctx *ctx, size_t low, size_t high)
{
	t_quicksort	qs;

	qs = (t_quicksort){0};
	qs.k = high - low + 1;
	if (qs.k <= 3)
		return (sort_small_b(ctx, qs.k));
	qs.p[0] = low + qs.k / 3;
	qs.p[1] = low + 2 * qs.k / 3;
	if (!partition_b(ctx, &qs))
		return (false);
	return (sort_a(ctx, qs.p[1], high)
		&& rotate_back(ctx, &ctx->a, qs.count[0], RRA)
		&& sort_a(ctx, qs.p[0], qs.p[1] - 1)
		&& rotate_back(ctx, &ctx->b, qs.count[1], RRB)
		&& sort_b(ctx, low, qs.p[0] - 1));
}

bool	sort_quicksort(t_ctx *ctx)
{
	return (sort_a(ctx, 0, ctx->a.cap - 1));
}
