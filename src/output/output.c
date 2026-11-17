/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfavier <noam.favier@learner.42.tech>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 20:19:18 by nfavier           #+#    #+#             */
/*   Updated: 2026/11/17 20:51:56 by nfavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

const char	*op_name(t_ops op)
{
	static const char *const	table[OP_COUNT] = {
		"sa", "sb", "ss",
		"pa", "pb",
		"ra", "rb", "rr",
		"rra", "rrb", "rrr",
	};

	return (table[op]);
}

bool	ops_flush(t_ctx *ctx)
{
	t_opbuf		*ops;
	const char	*name;
	size_t		i;

	i = (size_t)-1;
	ops = &ctx->ops;
	while (++i < ops->len)
	{
		name = op_name(((t_ops){ops->data[i]}));
		if (ft_printf("%s\n", name) == -1)
			return (false);
	}
	return (true);
}
