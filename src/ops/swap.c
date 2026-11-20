/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfavier <noam.favier@learner.42.tech>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 12:03:46 by nfavier           #+#    #+#             */
/*   Updated: 2026/11/17 15:31:32 by nfavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ops.h"

/* < 2 elements: nothing to swap, nothing happens */
static void	swap(t_stack *s)
{
	int	tmp;

	if (s->curr_size < 2)
		return ;
	tmp = stack_get(s, 0);
	stack_set(s, 0, stack_get(s, 1));
	stack_set(s, 1, tmp);
}

void	swap_a(t_ctx *ctx)
{
	swap(&ctx->a);
}

void	swap_b(t_ctx *ctx)
{
	swap(&ctx->b);
}

void	swap_both(t_ctx *ctx)
{
	swap(&ctx->a);
	swap(&ctx->b);
}
