/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 15:28:14 by bopopovi          #+#    #+#             */
/*   Updated: 2018/07/28 23:33:50 by bopopovi         ###   ########.fr       */
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
#include <locale.h>

#define BUFF_SIZE 64
#define MAX_INT_LEN 21
#define HEXA "0123456789abcdef"
#define HEXA_UP "0123456789ABCDEF"
#define OCTAL "01234567"
#define BINARY "01"
#define DENARY "0123456789"
#define SPECIF ptf->specifier
#define WIDTH ptf->width
#define PRECISION ptf->precision
#define POS ptf->buff.pos
#define FMT ptf->fmt.format
#define INDEX ptf->fmt.index
#define FLAGS ptf->flags

typedef struct		s_fmt
{
	const char		*format;
	int				index;
}					t_fmt;

typedef struct		s_buff
{
	char			buff[BUFF_SIZE + 1];
	size_t			pos;
	size_t			read;
}					t_buff;

typedef struct		s_ptf
{
	struct s_buff	buff;
	struct s_fmt	fmt;
	int				width;
	int				precision;
	char			specifier;
	char			flags[11];
	char			*base;
}					t_ptf;

int		ft_printf(const char * restrict format, ...);
char	*ft_ftoa(double val, int precision, char *buff);
int		parse_input(t_ptf *ptf, va_list ap);
int		buff_append(t_ptf *ptf, char *input, int size);
int		treat_arg(t_ptf *ptf, va_list ap);
int		ft_printf_is_fspecif(int c);
int		treat_arg_type_int(t_ptf *ptf, long long param);
int			treat_arg_type_uint(t_ptf *ptf, long long param);
int		ft_printf_itoa(char *buff, int64_t val);
int		ft_printf_uitoa(char *buff, uint64_t val);
int		treat_arg_type_str(t_ptf *ptf, wchar_t *param);
int		ft_vprintf(const char * restrict format, va_list ap);
int		treat_arg_type_wcstr(t_ptf *ptf, wchar_t *wcstr, size_t size);
int		treat_arg_type_dbl(t_ptf *ptf, long long param);
int		treat_arg_type_base(t_ptf *ptf, long long param);
int		ft_printf_itoa_base(char *buff, char *charset, long long nbr);
int		ft_printf_uitoa_base(char *buff, char *charset, uint64_t nbr);
size_t	ft_wcslen(wchar_t *wcs);
int			get_flags(t_ptf *ptf, int i);
int			treat_precision(t_ptf *ptf, char *input, int arg_size);
int				print_arg(t_ptf *ptf, int *prefix, int *input, int size);
void		reset_flags(t_ptf *ptf);
int			treat_specifier_by_type(t_ptf *ptf, long long param);
void		save_flags(t_ptf *ptf, int c, int i);
int			ft_printf_is_flag(char c);
int		ft_printf_atoi(const char *str, int *res);
int			buff_seqncat(t_ptf *ptf, char *input, int n);
long long		get_varg(t_ptf *ptf, va_list ap);
long long		get_varg_int(t_ptf *ptf, va_list ap);
long long		get_varg_uint(t_ptf *ptf, va_list ap);
void				treat_htag(t_ptf *ptf, char *input, int arg_size);
char*			treat_flag_plus(t_ptf *ptf, char *input);
int			get_width_and_precision(t_ptf *ptf, char type, int size);

int				print_wcs(t_ptf *ptf, int *input, int size);
void			dump_fmt(t_ptf *ptf);
size_t			ft_wcsnlen(wchar_t *wcs, size_t n);
int			init_struct(t_ptf *ptf, const char * restrict format);
int			treat_arg_type_char(t_ptf *ptf, wchar_t param);
int			get_prefix(t_ptf *ptf, char *ptr, char *prefix);

#endif
