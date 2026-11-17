/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfavier <noam.favier@learner.42.tech>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 14:40:26 by nfavier           #+#    #+#             */
/*   Updated: 2026/11/17 15:02:47 by nfavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

int	stack_get(const t_stack *s, size_t i)
{
	return (s->value[(s->top + i) % s->cap]);
}

bool	stack_is_sorted(const t_stack *s)
{
	size_t	index;

	index = s->top;
	while (index < s->curr_size)
		if (s->value[index] > s->value[index + 1])
			return (0);
	return (1);
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
