/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfavier <noam.favier@learner.42.tech>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 22:16:44 by nfavier           #+#    #+#             */
/*   Updated: 2026/11/18 15:53:58 by nfavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_dprintf(int fd, const char *format, ...)
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
			ret = dispatch(fd, format[++i], &ap);
		else
			ret = write(fd, &format[i], 1);
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
