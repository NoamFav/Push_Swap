/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfavier <noam.favier@learner.42.tech>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 15:20:47 by nfavier           #+#    #+#             */
/*   Updated: 2026/11/17 15:21:05 by nfavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

/* op buffer */
bool		opbuf_init(t_opbuf *buf, size_t n);
bool		opbuf_push(t_opbuf *buf, t_ops op);
void		opbuf_free(t_opbuf *buf);

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
