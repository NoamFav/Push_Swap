/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfavier <noam.favier@learner.42.tech>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 14:40:26 by nfavier           #+#    #+#             */
/*   Updated: 2026/11/17 15:45:11 by nfavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	stack_get(const t_stack *s, size_t i)
{
	return (s->value[(s->top + i) % s->cap]);
}

void	stack_set(t_stack *s, size_t i, int v)
{
	s->value[(s->top + i) % s->cap] = v;
}

bool	stack_is_sorted(const t_stack *s)
{
	size_t	index;

	index = (size_t) - 1;
	while (++index + 1 < s->curr_size)
		if (stack_get(s, index) > stack_get(s, index + 1))
			return (false);
	return (true);
}

int	stack_pop(t_stack *s)
{
	int	v;

	v = s->value[s->top];
	s->top = (s->top + 1) % s->cap;
	s->curr_size--;
	return (v);
}

void	stack_push(t_stack *s, int v)
{
	s->top = (s->top + s->cap - 1) % s->cap;
	s->value[s->top] = v;
	s->curr_size++;
}
