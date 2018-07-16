/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 15:28:14 by bopopovi          #+#    #+#             */
/*   Updated: 2018/07/16 20:59:54 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include "./libft.h"
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define BUFF_SIZE 64
#define MAX_INT_LEN 21

typedef struct		s_flags
{
	bool			htag;
	bool			zero;
	bool			minus;
	bool			space;
	char			plus;
	bool			apos;
	bool			j;
	bool			z;
	char			l;
	char			h;
	int				width;
	int				precision;
	char			specifier;
}					t_flags;

typedef struct		s_buff
{
	char			buff[BUFF_SIZE + 1];
	size_t			pos;
	size_t			read;
	t_flags			flags;
}					t_buff;

int		ft_printf(const char * restrict format, ...);
char	*ft_ftoa(double val, int precision, char *buff);
int		parse_input(char *fmt, t_buff *buff, va_list ap);
int		buff_append(t_buff *buff, char *input, int size);
int		treat_arg(t_buff *buff, char **input, va_list ap);
int		ft_printf_is_fspecif(int c);
int		treat_arg_type_int(t_buff *buff, char type, va_list ap);
int			treat_arg_type_uint(t_buff *buff, char type, va_list ap);
int		ft_printf_itoa(char *buff, int64_t val);
int		ft_printf_uitoa(char *buff, uint64_t val);
int		treat_arg_type_str(t_buff *buff, char type, va_list ap);
int		ft_vprintf(const char * restrict format, va_list ap);
int		treat_arg_type_wcstr(t_buff *buff, wchar_t *wcstr, size_t size);
int		treat_arg_type_dbl(t_buff *buff, char type, va_list ap);
int		treat_arg_type_base(t_buff *buff, char type, va_list ap);
int		ft_printf_itoa_base(char *buff, int base, uint64_t nbr);
size_t	ft_wcslen(wchar_t *wcs);
int			get_flags(t_buff *buff, char **input, int i);
int			treat_precision(t_buff *buff, char *input, int arg_size);
int			print_arg(t_buff *buff, char *input, int size);
void		reset_flags(t_flags *flags);
int		(*treat_specifier_by_type(char specifier))(t_buff*, char, va_list);
void		save_flags(t_buff *buff, int c, int i);
int			ft_printf_is_flag(char c);
int		ft_printf_atoi(const char *str, int *res);
int			buff_seqncat(t_buff *buff, char *input, int n);

#endif
