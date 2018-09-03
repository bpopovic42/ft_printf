/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 19:06:52 by bopopovi          #+#    #+#             */
/*   Updated: 2018/09/03 19:18:29 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Check wether provided specifier exists or if it is a '%'
** If specifier isn't recognized it is treated as the arg to a 'c' conversion
** Else send specifier's corresponding va_arg to the associated function
** Returns size of treated argument in case of success, -1 otherwise
*/

static int				treat_arg_by_type(t_ptf *ptf, va_list ap)
{
	char spec;

	spec = ptf->spec;
	if (!ft_printf_is_spec(spec) || spec == '%')
	{
		ptf->spec = 'c';
		if (spec == '%')
		{
			ptf->width--;
			ptf->precision = -1;
			return (ft_printf_print_arg(ptf, "\0", "%", 1));
		}
		return (ft_printf_type_char(ptf, (wchar_t)spec));
	}
	else if (ft_strchr("bBdDioOuUxXp", spec))
		return (ft_printf_type_int(ptf, va_arg(ap, long long)));
	else if (spec == 'r' || spec == 's' || spec == 'S')
		return (ft_printf_type_str(ptf, (wchar_t*)va_arg(ap, long long)));
	else if (spec == 'c' || spec == 'C')
		return (ft_printf_type_char(ptf, (wchar_t)va_arg(ap, long long)));
	else if (ft_strchr("aAeEfFgG", spec))
		return (ft_printf_type_dbl(ptf, va_arg(ap, double)));
	else if (spec == 'n')
		return (ft_printf_type_n(ptf, va_arg(ap, int*)));
	return (-1);
}

/*
** Called if a '%' has been encountered and that it wasn't followed by a '\0'
** Returns size of treated argument if flags weren't directly followed by '\0'
** Returns 0 otherwise
*/

static int				treat_arg(t_ptf *ptf, va_list ap)
{
	int			i;
	int			size;

	i = 1;
	size = 0;
	i = ft_printf_get_flags(ptf, ap, i + ptf->fmt.i) - ptf->fmt.i;
	if (ptf->spec)
	{
		size = treat_arg_by_type(ptf, ap);
		ptf->fmt.format += i + 1;
		ptf->fmt.i = 0;
	}
	return (size);
}

/*
** Parse the format string for '%' or '{' until its end
** Add rest of the format string to buffer if anything's left
** Returns totabl nbr of characters written in case of success, -1 otherwise
*/

static int				parse_fmt(t_ptf *ptf, va_list ap)
{
	int				ret;
	const char		**fmt;
	long long		*i;

	ret = 0;
	fmt = &(ptf->fmt.format);
	i = &(ptf->fmt.i);
	while ((*fmt)[*i])
	{
		while ((*fmt)[*i] && (*fmt)[*i] != '%' && (*fmt)[*i] != '{')
			(*i)++;
		if ((*fmt)[*i] == '%')
		{
			if (!(*fmt)[*i + 1])
				break ;
			else if ((ret = treat_arg(ptf, ap)) < 1)
				return (ret);
		}
		else if ((*fmt)[*i] == '{')
			*i += ft_printf_color(ptf);
	}
	if (**fmt)
		ft_printf_buff_cat(ptf, (char*)*fmt, *i);
	return (ptf->buff.read);
}

/*
** Initialize ptf structure and send input to parse_fmt
** Write what's left in the buffer and terminate
** Returns total nbr of characters written in case of success, -1 otherwise
*/

int						ft_vprintf(const char *restrict format, va_list ap)
{
	int				ret;
	t_ptf			ptf;

	ptf.buff.pos = 0;
	ptf.buff.read = 0;
	ptf.fmt.format = format;
	ptf.fmt.i = 0;
	if ((ret = parse_fmt(&ptf, ap)) < 0)
	{
		write(1, ptf.buff.buff, ptf.buff.pos);
		return (-1);
	}
	if (ptf.buff.pos > 0)
	{
		write(1, ptf.buff.buff, ptf.buff.pos);
		ptf.buff.read += ptf.buff.pos;
	}
	return (ptf.buff.read);
}
