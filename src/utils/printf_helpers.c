/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfavier <noam.favier@learner.42.tech>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 23:28:19 by nfavier           #+#    #+#             */
/*   Updated: 2026/11/18 15:07:19 by nfavier          ###   ########.fr       */
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

int	put_base(unsigned long n, char *base)
{
	char	buf[65];
	int		len;

	if (n == 0)
		return (write(1, "0", 1));
	len = ft_decimal_to_base(buf, n, base);
	return (write(1, buf, len));
}

int	put_int(int n)
{
	long	nb;
	int		sign;
	int		ret;

	nb = n;
	sign = 0;
	if (nb < 0)
	{
		sign = write(1, "-", 1);
		nb = -nb;
	}
	ret = put_base(nb, BASE_10);
	if (sign == -1 || ret == -1)
		return (-1);
	return (ret + sign);
}

int	put_ptr(void *p)
{
	int	count;
	int	len;

	if (!p)
		return (write(1, "(nil)", 5));
	count = write(1, "0x", 2);
	len = put_base((unsigned long)p, BASE_16);
	if (len == -1 || count == -1)
		return (-1);
	return (len + count);
}

int	put_str(char *str)
{
	if (!str)
		return (write(1, "(null)", 6));
	return (write(1, str, ft_strlen(str)));
}
