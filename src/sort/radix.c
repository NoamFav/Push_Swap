/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajanssen <ajanssen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 01:04:33 by ajanssen          #+#    #+#             */
/*   Updated: 2026/11/18 23:11:18 by nfavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

static bool	push_back(t_ctx *ctx, int bit, bool last)
{
	size_t	k;

	k = ctx->b.curr_size;
	while (k--)
	{
		if (last || (stack_get(&ctx->b, 0) >> (bit + 1)) & 1)
		{
			if (!do_op(ctx, PA))
				return (false);
		}
		else if (!do_op(ctx, RB))
			return (false);
	}
	return (true);
}

static bool	radix_pass(t_ctx *ctx, int bit, bool last)
{
	size_t	k;

	k = ctx->a.curr_size;
	while (k--)
	{
		if ((stack_get(&ctx->a, 0) >> bit) & 1)
		{
			if (!do_op(ctx, RA))
				return (false);
		}
		else if (!do_op(ctx, PB))
			return (false);
	}
	return (push_back(ctx, bit, last));
}

/*
** LSD radix sort in base 2.
** Compressing values to 0..n-1 is required beforehand.
** We push all numbers with 0-bits to b, then put them back.
** Starting with the least significant bit makes it stable.
** The number of bits is ceil(log2 n) = the number of passes,
** and we go over all numbers each time, so it runs in O(n log n).
*/
bool	sort_radix(t_ctx *ctx)
{
	int	bits;
	int	bit;

	bits = 0;
	while (((ctx->a.curr_size - 1) >> bits) != 0)
		bits++;
	bit = -1;
	while (++bit < bits)
	{
		if (ctx->b.curr_size == 0 && stack_is_sorted(&ctx->a))
			return (true);
		if (!radix_pass(ctx, bit, bit + 1 == bits))
			return (false);
	}
	return (true);
}
