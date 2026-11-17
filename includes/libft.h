/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfavier <noam.favier@learner.42.tech>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 20:37:58 by nfavier           #+#    #+#             */
/*   Updated: 2026/11/17 20:45:05 by nfavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <stdarg.h>

# define BASE_16_UP "0123456789ABCDEF"
# define BASE_16 "0123456789abcdef"
# define BASE_10 "0123456789"

size_t	ft_strlen(const char *str);
int		ft_printf(const char *format, ...);
int		dispatch(char c, va_list *ap);
int		put_base(unsigned long n, char *base);
int		put_int(int n);
int		put_ptr(void *p);
int		put_str(char *str);
#endif
