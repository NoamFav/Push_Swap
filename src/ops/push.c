/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfavier <noam.favier@learner.42.tech>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 14:26:35 by nfavier           #+#    #+#             */
/*   Updated: 2026/11/17 15:40:12 by nfavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ops.h"

/* pushes s2 onto s1. empty s2 = no-op, like the subject says */
static void	push(t_stack *s1, t_stack *s2)
{
	if (s2->curr_size == 0)
		return ;
	stack_push(s1, stack_pop(s2));
}

void	push_a(t_ctx *ctx)
{
	push(&ctx->a, &ctx->b);
}

void	push_b(t_ctx *ctx)
{
	push(&ctx->b, &ctx->a);
}
