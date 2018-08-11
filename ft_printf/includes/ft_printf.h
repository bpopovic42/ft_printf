/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 15:28:14 by bopopovi          #+#    #+#             */
/*   Updated: 2018/08/11 02:59:02 by bopopovi         ###   ########.fr       */
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

#define BUFF_SIZE 128
#define MAX_INT_LEN 21
#define HEXA "0123456789abcdef"
#define HEXA_UP "0123456789ABCDEF"
#define OCTAL "01234567"
#define BINARY "01"
#define DENARY "0123456789"
#define SPEC ptf->specifier
#define WIDTH ptf->width
#define PRECISION ptf->precision
#define POS ptf->buff.pos
#define FMT ptf->fmt.format
#define INDEX ptf->fmt.index
#define FLAGS ptf->flags

typedef struct		s_fmt
{
	const char		*format;
	long long		index;
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

/*
** FT_VPRINTF
*/

int		ft_vprintf(const char * restrict format, va_list ap);

/*
** FT_PRINTF_BUFFER
*/

int		buff_append(t_ptf *ptf, char *input, int size);
void	buff_seqncat(t_ptf *ptf, char *input, long long n);

/*
** FT_PRINTF_TOOLS
*/

int		ft_printf_is_flag(int c);
int		ft_printf_is_spec(int c);
size_t	ft_printf_atoi(const char *str, int *res);
void	dump_fmt(t_ptf *ptf);
int		ft_printf_itoa_base(char *buff, char *charset, long long nbr);
int		ft_printf_uitoa_base(char *buff, char *charset, uint64_t nbr);

/*
** FT_PRINTF_PRINT_ARG
*/

int		ft_printf_print_arg(t_ptf *ptf, int *prfx, int *input, int size);
int		ft_printf_print_wcs(t_ptf *ptf, int *input, int size);

/*
** TYPES
*/

int		treat_arg_type_int(t_ptf *ptf, long long param);
int		treat_arg_type_str(t_ptf *ptf, wchar_t *param);
int		treat_arg_type_char(t_ptf *ptf, wchar_t param);
int		treat_arg_type_dbl(t_ptf *ptf, double param);



int		ft_printf_get_flags(t_ptf *ptf, va_list ap, int i);



size_t	ft_wcslen(wchar_t *wcs);
size_t	ft_wcsnlen(wchar_t *wcs, size_t n);
char	*ft_ftoa(double val, int precision, char *buff);

#endif
