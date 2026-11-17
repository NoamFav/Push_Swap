/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noamfavier <noam.favier@learner.42.tech>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 22:16:44 by noamfavier        #+#    #+#             */
/*   Updated: 2026/11/17 20:42:37 by nfavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	dispatch(char c, va_list *ap)
{
	if (c == 'c')
		return (write(1, &(char){va_arg(*ap, int)}, 1));
	if (c == 'd' || c == 'i')
		return (put_int(va_arg(*ap, int)));
	if (c == 'x')
		return (put_base(va_arg(*ap, unsigned int), BASE_16));
	if (c == 'X')
		return (put_base(va_arg(*ap, unsigned int), BASE_16_UP));
	if (c == 'u')
		return (put_base(va_arg(*ap, unsigned int), BASE_10));
	if (c == 's')
		return (put_str(va_arg(*ap, char *)));
	if (c == 'p')
		return (put_ptr(va_arg(*ap, void *)));
	if (c == '%')
		return (write(1, "%", 1));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	size_t	i;
	int		ret;
	size_t	count;

	i = 0;
	count = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
			ret = dispatch(format[++i], &ap);
		else
			ret = write(1, &format[i], 1);
		if (ret == -1)
		{
			va_end(ap);
			return (-1);
		}
		count += ret;
		i++;
	}
	va_end(ap);
	return (count);
}
