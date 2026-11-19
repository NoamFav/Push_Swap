/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfavier <noam.favier@learner.42.tech>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 22:31:06 by nfavier           #+#    #+#             */
/*   Updated: 2026/11/19 11:14:51 by ajanssen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SORT_H
# define SORT_H
# include "push_swap.h"

bool	sort_run(t_ctx *ctx, t_conf *conf);
bool	sort_bubble(t_ctx *ctx);
bool	sort_selection(t_ctx *ctx);
bool	sort_radix(t_ctx *ctx);

/* Quickway sort and its little happy family*/
bool	quick_sort(t_ctx *ctx);
bool	sort_a(t_ctx *ctx, size_t low, size_t high);
bool	sort_b(t_ctx *ctx, size_t low, size_t high);
bool	sort_small_a(t_ctx *ctx, int k);
bool	sort_small_b(t_ctx *ctx, int k);
bool	rotate_back(t_ctx *ctx, t_stack *s, size_t count, t_ops op);

#endif
