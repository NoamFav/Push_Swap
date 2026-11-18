/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dprintf_dispatch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfavier <noam.favier@learner.42.tech>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 15:30:36 by nfavier           #+#    #+#             */
/*   Updated: 2026/11/18 16:05:36 by nfavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	dispatch(int fd, char c, va_list *ap)
{
	if (c == 'c')
		return (write(fd, &(char){va_arg(*ap, int)}, 1));
	if (c == 'd' || c == 'i')
		return (put_int(fd, va_arg(*ap, int)));
	if (c == 'x')
		return (put_base(fd, va_arg(*ap, unsigned int), BASE_16));
	if (c == 'X')
		return (put_base(fd, va_arg(*ap, unsigned int), BASE_16_UP));
	if (c == 'u')
		return (put_base(fd, va_arg(*ap, unsigned int), BASE_10));
	if (c == 's')
		return (put_str(fd, va_arg(*ap, char *)));
	if (c == 'p')
		return (put_ptr(fd, va_arg(*ap, void *)));
	if (c == 'P')
		return (put_double(fd, va_arg(*ap, double)));
	if (c == '%')
		return (write(fd, "%", 1));
	return (0);
}

int	put_int(int fd, int n)
{
	long	nb;
	int		sign;
	int		ret;

	nb = n;
	sign = 0;
	if (nb < 0)
	{
		sign = write(fd, "-", 1);
		nb = -nb;
	}
	ret = put_base(fd, nb, BASE_10);
	if (sign == -1 || ret == -1)
		return (-1);
	return (ret + sign);
}

int	put_ptr(int fd, void *p)
{
	int	count;
	int	len;

	if (!p)
		return (write(fd, "(nil)", 5));
	count = write(fd, "0x", 2);
	len = put_base(fd, (unsigned long)p, BASE_16);
	if (len == -1 || count == -1)
		return (-1);
	return (len + count);
}

int	put_str(int fd, char *str)
{
	if (!str)
		return (write(fd, "(null)", 6));
	return (write(fd, str, ft_strlen(str)));
}

int	put_double(int fd, double num)
{
	int	pct;
	int	digit;
	int	decimal1;
	int	decimal2;

	pct = (long)(num * 10000 + 0.5);
	digit = put_int(fd, pct / 100);
	if (write(fd, ".", 1) == -1)
		return (-1);
	decimal1 = put_int(fd, pct / 10 % 10);
	decimal2 = put_int(fd, pct % 10);
	if (digit == -1 || decimal1 == -1 || decimal2 == -1)
		return (-1);
	return (digit + 1 + decimal1 + decimal2);
}
