/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disorder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajanssen <ajanssen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 22:50:52 by ajanssen          #+#    #+#             */
/*   Updated: 2026/11/16 22:50:54 by ajanssen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

double	compute_disorder(t_ctx *c)
{
	size_t	i;
	size_t	j;
	size_t	total;
	size_t	mistakes;

	total = 0;
	mistakes = 0;
	i = 0;
	while (i < c->a.curr_size)
	{
		j = i + 1;
		while (j < c->a.curr_size)
		{
			total++;
			if (stack_get(&c->a, i) > stack_get(&c->a, j))
				mistakes++;
			j++;
		}
		i++;
	}
	if (total == 0)
		return (0);
	return ((double)mistakes / total);
}
