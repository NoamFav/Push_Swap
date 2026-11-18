/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajanssen <ajanssen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 01:04:33 by ajanssen          #+#    #+#             */
/*   Updated: 2026/11/18 01:04:35 by ajanssen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* f**ck**g norminette that wants curly braces */
/* the PA pass can be optimized */
static bool	radix_pass(t_ctx *ctx, int bit, int n)
{
	int	i;

	i = -1;
	while (++i < n)
	{
		if ((stack_get(&ctx->a, 0) >> bit) & 1)
		{
			if (!do_op(ctx, RA))
				return (false);
		}
		else if (!do_op(ctx, PB))
			return (false);
	}
	while (ctx->b.curr_size > 0)
		if (!do_op(ctx, PA))
			return (false);
	return (true);
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
	int	n;
	int	bit;

	n = ctx->a.curr_size;
	bit = 0;
	while (!stack_is_sorted(&ctx->a))
	{
		if (!radix_pass(ctx, bit, n))
			return (false);
		bit++;
	}
	return (true);
}
