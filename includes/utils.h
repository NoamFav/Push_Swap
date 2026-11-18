/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfavier <noam.favier@learner.42.tech>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 20:37:58 by nfavier           #+#    #+#             */
/*   Updated: 2026/11/18 15:46:17 by nfavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>

# define BASE_16_UP "0123456789ABCDEF"
# define BASE_16 "0123456789abcdef"
# define BASE_10 "0123456789"

size_t	ft_strlen(const char *str);
int		ft_strcmp(const char *a, const char *b);
int		ft_dprintf(int fd, const char *format, ...);
int		dispatch(int fd, char c, va_list *ap);
int		put_base(int fd, unsigned long n, char *base);
int		put_int(int fd, int n);
int		put_ptr(int fd, void *p);
int		put_str(int fd, char *str);
int		put_double(int fd, double num);

#endif
