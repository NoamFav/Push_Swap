/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajanssen <ajanssen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 22:46:56 by ajanssen          #+#    #+#             */
/*   Updated: 2026/11/19 15:02:05 by nfavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "sort.h"

static t_strategy	choose_strategy(const t_conf *conf)
{
	if (conf->strat != ADAPTIVE)
		return (conf->strat);
	if (conf->disorder < 0.2)
		return (SIMPLE);
	if (conf->disorder < 0.5)
		return (MEDIUM);
	return (COMPLEX);
}

bool	sort_run(t_ctx *ctx, t_conf *conf)
{
	if (stack_is_sorted(&ctx->a))
		return (true);
	if (ctx->a.curr_size <= 3)
		return (sort_small_a(ctx, ctx->a.curr_size));
	else if (ctx->a.curr_size <= 5)
		return (sort_quicksort(ctx));
	conf->picked = choose_strategy(conf);
	if (conf->picked == SIMPLE)
		return (sort_selection(ctx));
	if (conf->picked == MEDIUM)
		return (sort_radix(ctx));
	return (sort_quicksort(ctx));
}

// per instructions, no numbers (ret = 0) must exit silently
int	main(int argc, char **argv)
{
	int		ret;
	t_ctx	ctx;
	t_conf	conf;

	ret = parse_args(argc, argv, &ctx, &conf);
	if (ret < 0)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	if (ret == 0)
		return (0);
	conf.disorder = compute_disorder(&ctx);
	if (!sort_run(&ctx, &conf) || !ops_clean(&ctx) || !ops_flush(&ctx))
	{
		ctx_free(&ctx);
		return (1);
	}
	ctx_free(&ctx);
	return (0);
}
