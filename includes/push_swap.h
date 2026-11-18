/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfavier <noam.favier@learner.42.tech>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 18:35:01 by nfavier           #+#    #+#             */
/*   Updated: 2026/11/18 15:59:58 by nfavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

/* the 11 ops, in subject/bench order. OP_COUNT is the sentinel, not an op */
typedef enum e_OPS
{
	SA,
	SB,
	SS,
	PA,
	PB,
	RA,
	RB,
	RR,
	RRA,
	RRB,
	RRR,
	OP_COUNT,
}	t_ops;

/* ADAPTIVE is 0 on purpose: a zeroed conf defaults to it */
typedef enum e_STRATEGY
{
	ADAPTIVE,
	SIMPLE,
	MEDIUM,
	COMPLEX,
}	t_strategy;

/*
** ring buffer stack. values are ranks 0..n-1, never raw input.
** never read fields directly: use stack_get and friends below
*/
typedef struct s_stack
{
	int		*value;
	size_t	cap;
	size_t	top;
	size_t	curr_size;
}	t_stack;

/* growable list of recorded ops, one byte each */
typedef struct s_opbuf
{
	unsigned char	*data;
	size_t			len;
	size_t			cap;
}	t_opbuf;

/* everything a strategy gets. counts feeds --bench */
typedef struct s_ctx
{
	t_stack	a;
	t_stack	b;
	t_opbuf	ops;
	int		counts[OP_COUNT];
}	t_ctx;

/*
** parser output. strat is what was asked for, picked is what actually ran
** (adaptive resolves to one of the others). disorder is computed on the
** input before any op
*/
typedef struct s_conf
{
	t_strategy	strat;
	bool		bench;
	t_strategy	picked;
	double		disorder;
}	t_conf;

typedef void	(*t_opfn)(t_ctx *);

/*
** setup / teardown
** ctx_init takes the raw validated ints and normalises them to ranks.
** never called with n == 0: main exits silently when there are no args
*/
bool		ctx_init(t_ctx *ctx, int *values, size_t n);
void		ctx_free(t_ctx *ctx);
double		compute_disorder(t_ctx *c);

/* parsing */
int			parse_args(int argc, char **argv, t_ctx *ctx, t_conf *conf);
bool		parse_int(const char *s, int *out);
bool		has_dup(const int *v, size_t n);

/* read-only peeking. i is the position from the top, 0 = top */
int			stack_get(const t_stack *s, size_t i);
size_t		stack_min_pos(const t_stack *s);
size_t		stack_max_pos(const t_stack *s);
bool		stack_is_sorted(const t_stack *s);

/* stack edit, push becomes O(1) */
bool		stack_init(t_stack *s, size_t cap, size_t curr);
void		stack_set(t_stack *s, size_t i, int v);
void		stack_push(t_stack *s, int v);
int			stack_pop(t_stack *s);
/* op buffer */
bool		opbuf_init(t_opbuf *buf, size_t n);
bool		opbuf_push(t_opbuf *buf, t_ops op);
void		opbuf_free(t_opbuf *buf);

/* dispatcher: applies op, counts it, records it. false on malloc fail */
bool		do_op(t_ctx *ctx, t_ops op);

/* output */
const char	*op_name(t_ops op);
bool		ops_flush(t_ctx *ctx);

#endif
