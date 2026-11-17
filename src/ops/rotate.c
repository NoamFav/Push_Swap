/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfavier <noam.favier@learner.42.tech>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 15:30:37 by nfavier           #+#    #+#             */
/*   Updated: 2026/11/17 15:53:50 by nfavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ops.h"

static void	rotate(t_stack *s)
{
	s->value[(s->top + s->curr_size) % s->cap] = s->value[s->top];
	s->top = (s->top + 1) % s->cap;
}

void	rotate_a(t_ctx *ctx)
{
	rotate(&ctx->a);
}

void	rotate_b(t_ctx *ctx)
{
	rotate(&ctx->b);
}

void	rotate_both(t_ctx *ctx)
{
	rotate(&ctx->a);
	rotate(&ctx->b);
}
