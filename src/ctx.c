/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfavier <noam.favier@learner.42.tech>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 18:51:51 by nfavier           #+#    #+#             */
/*   Updated: 2026/11/18 15:54:57 by nfavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	get_rank(t_stack *s, int *values, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	count;

	i = (size_t)-1;
	while (++i < n)
	{
		count = 0;
		j = (size_t) - 1;
		while (++j < n)
			if (values[j] < values[i])
				count++;
		s->value[i] = count;
	}
}

bool	stack_init(t_stack *s, size_t cap, size_t curr)
{
	s->value = malloc(sizeof(int) * cap);
	if (!s->value)
		return (false);
	s->cap = cap;
	s->curr_size = curr;
	s->top = 0;
	return (true);
}

bool	ctx_init(t_ctx *ctx, int *values, size_t n)
{
	*ctx = (t_ctx){0};
	if (!stack_init(&ctx->a, n, n)
		|| !stack_init(&ctx->b, n, 0)
		|| !opbuf_init(&ctx->ops, n))
	{
		ctx_free(ctx);
		return (false);
	}
	get_rank(&ctx->a, values, n);
	return (true);
}

void	ctx_free(t_ctx *ctx)
{
	free(ctx->a.value);
	free(ctx->b.value);
	free(ctx->ops.data);
	*ctx = (t_ctx){0};
}
