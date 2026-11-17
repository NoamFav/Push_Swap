/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfavier <noam.favier@learner.42.tech>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 15:20:47 by nfavier           #+#    #+#             */
/*   Updated: 2026/11/17 18:56:42 by nfavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef OPS_H
# define OPS_H
# include "push_swap.h"
/* op functions: */
/* Push */
void		push_a(t_ctx *ctx);
void		push_b(t_ctx *ctx);

/* Swap */
void		swap_a(t_ctx *ctx);
void		swap_b(t_ctx *ctx);
void		swap_both(t_ctx *ctx);

/* Rotate */
void		rotate_a(t_ctx *ctx);
void		rotate_b(t_ctx *ctx);
void		rotate_both(t_ctx *ctx);

/* Reverse Rotate */
void		rrotate_a(t_ctx *ctx);
void		rrotate_b(t_ctx *ctx);
void		rrotate_both(t_ctx *ctx);

#endif
