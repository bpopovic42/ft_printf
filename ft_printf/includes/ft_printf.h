/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 15:28:14 by bopopovi          #+#    #+#             */
/*   Updated: 2018/06/23 19:54:14 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include "libft.h"
#include <stdarg.h>
#include <unistd.h>
#include <wchar.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

#define BUFF_SIZE 64

typedef struct		s_buff
{
	char			buff[BUFF_SIZE + 1];
	size_t			pos;
}					t_buff;

typedef union		u_dbl
{
	double			val;
	uint64_t		u64;
}					t_dbl;

int		ft_printf(const char * restrict format, ...);
t_list	*store_args(const char *restrict format, va_list ap);
int		parse_format(char **output, char **format, va_list ap, size_t *in_len, size_t *out_len);
size_t	parse_format_string(char **output, va_list ap, char *fmt);
int		fast_append(char **dst, char **app, size_t *dlen, size_t *alen);
int		get_format_arg(char *format, char **output, va_list ap);

void	fill_buffer(t_buff *buff, void *data, size_t size);
int		ft_wcstombs(char *s, wchar_t *wcs, size_t n);
int		ft_wctomb(char *s, wchar_t wc);

void	init_buffer(t_buff *buff);

char	*ft_ftoa(double val, int precision, char *buff);

#endif
