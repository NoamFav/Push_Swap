/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajanssen <ajanssen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 22:01:51 by ajanssen          #+#    #+#             */
/*   Updated: 2026/11/17 22:01:55 by ajanssen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** returns false if not a number, else true and fill the `out` variable
** the sign in `n*sign > INT_MAX` is needed to not falsely reject INT_MIN
*/
bool	parse_int(const char *s, int *out)
{
	long long	n;
	long long	sign;

	sign = 1;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	if (!*s)
		return (false);
	n = 0;
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (false);
		n = n * 10 + (*s - '0');
		if (n * sign > INT_MAX || n * sign < INT_MIN)
			return (false);
		s++;
	}
	*out = (int)(n * sign);
	return (true);
}

/* cf rules: we consider duplicate numbers invalid input (surprisingly) */
bool	has_dup(const int *v, size_t n)
{
	size_t	i;
	size_t	j;

	i = (size_t)-1;
	while (++i < n)
	{
		j = i;
		while (++j < n)
			if (v[i] == v[j])
				return (true);
	}
	return (false);
}
