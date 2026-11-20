/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rrotate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfavier <noam.favier@learner.42.tech>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 15:31:47 by nfavier           #+#    #+#             */
/*   Updated: 2026/11/17 15:31:55 by nfavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ops.h"

/* mirror of rotate: top steps back, the old bottom lands in it */
static void	rrotate(t_stack *s)
{
	if (s->curr_size < 2)
		return ;
	s->top = (s->top + s->cap - 1) % s->cap;
	s->value[s->top] = s->value[(s->top + s->curr_size) % s->cap];
}

void	rrotate_a(t_ctx *ctx)
{
	rrotate(&ctx->a);
}

void	rrotate_b(t_ctx *ctx)
{
	rrotate(&ctx->b);
}

void	rrotate_both(t_ctx *ctx)
{
	rrotate(&ctx->a);
	rrotate(&ctx->b);
}
