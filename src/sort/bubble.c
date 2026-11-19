/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre.janssen@learner.42.tech          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 09:33:58 by ajanssen          #+#    #+#             */
/*   Updated: 2026/11/19 11:22:25 by ajanssen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

/* if the top value is higher, move it up with SA then advance with RA */
static bool	bubble_step(t_ctx *ctx)
{
	if (stack_get(&ctx->a, 0) > stack_get(&ctx->a, 1)
		&& !do_op(ctx, SA))
		return (false);
	return (do_op(ctx, RA));
}

/* the constant is_sorted check is costly, but it doesn't affect the
** final ops outcome, and it keeps the code simple */
bool	sort_bubble(t_ctx *ctx)
{
	size_t	i;

	while (!stack_is_sorted(&ctx->a))
	{
		i = 0;
		while (++i < ctx->a.curr_size)
		{
			if (!bubble_step(ctx))
				return (false);
		}
		if (!do_op(ctx, RA))
			return (false);
	}
	return (true);
}


