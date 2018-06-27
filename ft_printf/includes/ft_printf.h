/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 15:28:14 by bopopovi          #+#    #+#             */
/*   Updated: 2018/06/27 14:15:20 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include "../libft/includes/libft.h"
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFF_SIZE 64
#define MAX_INT_LEN 21

typedef struct		s_buff
{
	char			buff[BUFF_SIZE + 1];
	size_t			pos;
}					t_buff;

int		ft_printf(const char * restrict format, ...);
int		ft_wcstombs(char *s, wchar_t *wcs, size_t n);
int		ft_wctomb(char *s, wchar_t wc);
char	*ft_ftoa(double val, int precision, char *buff);
int		parse_input(char *fmt, t_buff *buff, va_list ap);
int		buff_append(t_buff *buff, char *input, int size);
int		treat_arg(t_buff *buff, char **input, va_list ap);
int		ft_printf_is_fspecif(int c);
int		treat_arg_type_int(t_buff *buff, char type, va_list ap);
int		ft_printf_itoa(char *buff, int64_t val);
int		treat_arg_type_str(t_buff *buff, char type, va_list ap);
int		ft_vprintf(const char * restrict format, va_list ap);
int		treat_arg_type_wcstr(t_buff *buff, wchar_t *wcstr, size_t size);
int		treat_arg_type_dbl(t_buff *buff, char type, va_list ap);
int		treat_arg_type_base(t_buff *buff, char type, va_list ap);
int		ft_printf_itoa_base(char *buff, int base, int64_t nbr);
size_t	ft_wcslen(wchar_t *wcs);
int64_t	get_flags(uint64_t flags, char c);

#endif
