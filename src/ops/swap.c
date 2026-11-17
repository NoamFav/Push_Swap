/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfavier <noam.favier@learner.42.tech>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 12:03:46 by nfavier           #+#    #+#             */
/*   Updated: 2026/11/17 12:11:26 by nfavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap_a(t_ctx *ctx)
{
	int	tmp;

	if (ctx->a.curr_size < 2)
		return ;
	tmp = ctx->a.value[0];
	ctx->a.value[0] = ctx->a.value[1];
	ctx->a.value[1] = tmp;
	ctx->ops.data[ctx->ops.len++] = SA;
	ctx->counts[SA]++;
}

void	swap_b(t_ctx *ctx)
{
	int	tmp;

	if (ctx->b.curr_size < 2)
		return ;
	tmp = ctx->b.value[0];
	ctx->b.value[0] = ctx->b.value[1];
	ctx->b.value[1] = tmp;
	ctx->ops.data[ctx->ops.len++] = SB;
	ctx->counts[SB]++;
}

void	swap_both(t_ctx *ctx)
{
	swap_a(ctx);
	swap_b(ctx);
}
