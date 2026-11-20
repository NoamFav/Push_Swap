/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfavier <noam.favier@learner.42.tech>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 15:38:56 by nfavier           #+#    #+#             */
/*   Updated: 2026/11/20 16:39:29 by nfavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "utils.h"

static const char	*strat_name(t_strategy s)
{
	static const char	*names[] = {"Adaptive", "Simple", "Medium", "Complex"};

	return (names[s]);
}

static const char	*strat_class(t_strategy s)
{
	static const char	*classes[] = {"?", "O(n²)", "O(n√n)", "O(n log n)"};

	return (classes[s]);
}

/*
** stderr only, after the ops. name = what was asked for,
** class = what actually ran (adaptive picks one of the three)
*/
bool	bench_print(const t_ctx *ctx, const t_conf *conf)
{
	const int	*c;

	c = ctx->counts;
	return (ft_dprintf(2, "[bench] disorder: %P%%\n", conf->disorder) != -1
		&& ft_dprintf(2, "[bench] strategy: %s / %s\n",
			strat_name(conf->strat), strat_class(conf->picked)) != -1
		&& ft_dprintf(2, "[bench] total_ops: %u\n",
			(unsigned int)ctx->ops.len) != -1
		&& ft_dprintf(2, "[bench] sa: %d sb: %d ss: %d pa: %d pb: %d\n",
			c[SA], c[SB], c[SS], c[PA], c[PB]) != -1
		&& ft_dprintf(2, "[bench] ra: %d rb: %d rr: %d "
			"rra: %d rrb: %d rrr: %d\n",
			c[RA], c[RB], c[RR], c[RRA], c[RRB], c[RRR]) != -1);
}
