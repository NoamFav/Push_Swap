/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajanssen <ajanssen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 20:59:22 by ajanssen          #+#    #+#             */
/*   Updated: 2026/11/18 15:05:52 by nfavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "utils.h"

static bool	parse_option(const char *arg, t_conf *conf)
{
	if (ft_strcmp(arg, "--adaptive") == 0)
		conf->strat = ADAPTIVE;
	else if (ft_strcmp(arg, "--simple") == 0)
		conf->strat = SIMPLE;
	else if (ft_strcmp(arg, "--medium") == 0)
		conf->strat = MEDIUM;
	else if (ft_strcmp(arg, "--complex") == 0)
		conf->strat = COMPLEX;
	else if (ft_strcmp(arg, "--bench") == 0)
		conf->bench = true;
	else
		return (false);
	return (true);
}

/*
** returns the number count, -1 on error
** WARNING: currently, the last flag is saved
** unsure if multiple strategy flags is considered invalid input
*/
static int	read_args(int argc, char **argv, t_conf *conf, int *values)
{
	int	n;
	int	i;

	n = 0;
	i = 0;
	while (++i < argc)
	{
		if (argv[i][0] == '-' && argv[i][1] == '-')
		{
			if (!parse_option(argv[i], conf))
				return (-1);
		}
		else if (parse_int(argv[i], &values[n]))
			n++;
		else
			return (-1);
	}
	return (n);
}

/*
** returns -1 on error, 0 if nothing to sort, 1 if ctx is initialized correctly
** malloc is set to argc (and not argc - 1) to avoid malloc(0)
*/
int	parse_args(int argc, char **argv, t_ctx *ctx, t_conf *conf)
{
	int	*values;
	int	n;

	conf->strat = ADAPTIVE;
	conf->bench = false;
	conf->picked = ADAPTIVE;
	conf->disorder = 0.0;
	values = malloc(sizeof(int) * argc);
	if (!values)
		return (-1);
	n = read_args(argc, argv, conf, values);
	if (n > 0 && (has_dup(values, n) || !ctx_init(ctx, values, n)))
		n = -1;
	free(values);
	if (n < 0)
		return (-1);
	return (n > 0);
}
