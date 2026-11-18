/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dprintf_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfavier <noam.favier@learner.42.tech>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 23:28:19 by nfavier           #+#    #+#             */
/*   Updated: 2026/11/18 15:56:49 by nfavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	ft_decimal_to_base(char res[], unsigned long n, char *base)
{
	size_t	i;
	size_t	len;
	int		tmp;
	int		base_n;

	i = 0;
	tmp = 42;
	base_n = ft_strlen(base);
	while (n > 0)
	{
		res[i++] = base[n % base_n];
		n /= base_n;
	}
	len = i;
	i = (size_t)-1;
	while (++i < len / 2)
	{
		tmp = res[i];
		res[i] = res[len - i - 1];
		res[len - i - 1] = tmp;
	}
	return (len);
}

int	put_base(int fd, unsigned long n, char *base)
{
	char	buf[65];
	int		len;

	if (n == 0)
		return (write(fd, "0", 1));
	len = ft_decimal_to_base(buf, n, base);
	return (write(fd, buf, len));
}
