/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajanssen <ajanssen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 22:46:56 by ajanssen          #+#    #+#             */
/*   Updated: 2026/11/17 22:46:57 by ajanssen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// per instructions, no numbers (ret = 0) must exit silently
// OBVIOUSLY NOT FINISHED
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
}
