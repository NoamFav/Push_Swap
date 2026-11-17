/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfavier <noam.favier@learner.42.tech>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 14:26:35 by nfavier           #+#    #+#             */
/*   Updated: 2026/11/17 15:18:16 by nfavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

void	push_a(t_ctx *ctx)
{
	if (ctx->b.curr_size == 0)
		return ;
	stack_push(&ctx->a, stack_pop(&ctx->b));
}

void	push_b(t_ctx *ctx)
{
	if (ctx->a.curr_size == 0)
		return ;
	stack_push(&ctx->b, stack_pop(&ctx->a));
}
