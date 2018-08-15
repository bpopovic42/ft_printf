/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 15:28:14 by bopopovi          #+#    #+#             */
/*   Updated: 2018/08/15 19:27:42 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "./libft.h"
# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <locale.h>

# define FT_PRINTF_BUFF_SIZE 128
# define MAX_INT_LEN 21

typedef struct		s_fmt
{
	const char		*format;
	long long		i;
}					t_fmt;

typedef struct		s_buff
{
	char			buff[FT_PRINTF_BUFF_SIZE + 1];
	size_t			pos;
	size_t			read;
}					t_buff;

typedef struct		s_ptf
{
	struct s_buff	buff;
	struct s_fmt	fmt;
	int				width;
	int				precision;
	char			spec;
	char			flags[11];
	char			*base;
}					t_ptf;

typedef union		u_flt
{
	double			nbr;
	struct
	{
		unsigned long	mant: 52;
		unsigned int	expn: 11;
		unsigned int	sign: 1;
	} bits;
}					t_flt;

/*
** FT_PRINTF
*/

int		ft_printf(const char * restrict format, ...);
int		ft_vprintf(const char * restrict format, va_list ap);

/*
** FT_PRINTF_TYPE
*/

int		ft_printf_type_int(t_ptf *ptf, long long param);
int		ft_printf_type_str(t_ptf *ptf, wchar_t *param);
int		ft_printf_type_char(t_ptf *ptf, wchar_t param);
int		ft_printf_type_dbl(t_ptf *ptf, double param);

/*
** FT_PRINTF_GET_FLAGS
*/

int		ft_printf_get_flags(t_ptf *ptf, va_list ap, int i);

/*
** FT_PRINTF_PRINT_ARG
*/

int		ft_printf_print_arg(t_ptf *ptf, int *prfx, int *input, int size);
int		ft_printf_print_wcs(t_ptf *ptf, int *input, int size);

/*
** FT_PRINTF_BUFFER
*/

void	ft_printf_buff_cat(t_ptf *ptf, char *input, int size);
void	ft_printf_buff_catn(t_ptf *ptf, char *input, long long n);
void	ft_printf_dump_fmt(t_ptf *ptf);

/*
** FT_PRINTF_TOOLS
*/

int		ft_printf_is_flag(int c);
int		ft_printf_is_spec(int c);
size_t	ft_printf_atoi(const char *str, int *res);
int		ft_printf_itoa_base(char *buff, char *charset, long long nbr);
int		ft_printf_uitoa_base(char *buff, char *charset, uint64_t nbr);

#endif
