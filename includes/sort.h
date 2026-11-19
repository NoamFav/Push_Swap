/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfavier <noam.favier@learner.42.tech>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 22:31:06 by nfavier           #+#    #+#             */
/*   Updated: 2026/11/19 14:53:04 by nfavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SORT_H
# define SORT_H
# include "push_swap.h"

typedef struct s_quicksort
{
	int		k;
	t_ops	op;
	int		p[2];
	size_t	count[2];
}	t_quicksort;

/* Utils */
bool	sort_small_a(t_ctx *ctx, int k);
bool	sort_small_b(t_ctx *ctx, int k);

/* Algorithms */
bool	sort_run(t_ctx *ctx, t_conf *conf);
bool	sort_bubble(t_ctx *ctx);
bool	sort_selection(t_ctx *ctx);
bool	sort_radix(t_ctx *ctx);
bool	sort_quicksort(t_ctx *ctx);

/* Quickway sort and its little happy family*/
bool	sort_a(t_ctx *ctx, size_t low, size_t high);
bool	sort_b(t_ctx *ctx, size_t low, size_t high);
bool	partition_a(t_ctx *ctx, t_quicksort *qs);
bool	partition_b(t_ctx *ctx, t_quicksort *qs);
bool	rotate_back(t_ctx *ctx, t_stack *s, size_t count, t_ops op);

#endif
