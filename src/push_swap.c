/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajanssen <ajanssen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 22:46:56 by ajanssen          #+#    #+#             */
/*   Updated: 2026/11/18 23:41:31 by nfavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "sort.h"

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
	if (!quick_sort(&ctx) || !ops_flush(&ctx))
	{
		ctx_free(&ctx);
		return (1);
	}
	ctx_free(&ctx);
	return (0);
}
