/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 19:06:52 by bopopovi          #+#    #+#             */
/*   Updated: 2018/08/11 03:44:18 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		treat_arg_by_type(t_ptf *ptf, va_list ap)
{
	char invalid;

	invalid = ptf->spec;
	if (!ft_printf_is_spec(ptf->spec) || ptf->spec == '%')
	{
		ptf->spec = ptf->spec == '%' ? '%' : 'c';
		if (ptf->spec == '%')
		{
			ptf->width--;
			ptf->precision = -1;
			return (ft_printf_print_arg(ptf, (int*)"\0", (int*)"%", 1));
		}
		else
			return (ft_printf_type_char(ptf, (wchar_t)invalid));
	}
	else if (ft_strchr("sS", ptf->spec))
		return (ft_printf_type_str(ptf, (wchar_t*)va_arg(ap, long long)));
	else if (ft_strchr("cC", ptf->spec))
		return (ft_printf_type_char(ptf, (wchar_t)va_arg(ap, long long)));
	else if (ft_strchr("dDioOuUxXp", ptf->spec))
		return (ft_printf_type_int(ptf, va_arg(ap, long long)));
	else if (ft_strchr("fF", ptf->spec))
		return(ft_printf_type_dbl(ptf, va_arg(ap, double)));
	return (-1);
}

static int			treat_arg(t_ptf *ptf, va_list ap)
{
	int			i;
	int			size;

	i = 1;
	size = 0;
	if ((i = ft_printf_get_flags(ptf, ap, i + ptf->fmt.i) - ptf->fmt.i) < 1)
		return (i);
	size = treat_arg_by_type(ptf, ap);
	ptf->fmt.format += i + 1;
	ptf->fmt.i = 0;
	return (size);
}

static int			parse_fmt(t_ptf *ptf, va_list ap)
{
	int		ret;

	ret = 0;
	while (*ptf->fmt.format && ptf->fmt.format[ptf->fmt.i])
	{
		if (ptf->fmt.format[ptf->fmt.i] == '%' && ptf->fmt.format[ptf->fmt.i + 1])
		{
			if ((ret = treat_arg(ptf, ap)) <= 0)
				return (ret);
		}
		else if (ptf->fmt.format[ptf->fmt.i] == '%' && !ptf->fmt.format[ptf->fmt.i + 1])
		{
			ft_printf_dump_fmt(ptf);
			ptf->fmt.format += ptf->fmt.i + 1;
			ptf->fmt.i = 0;
		}
		else
			ptf->fmt.i++;
	}
	if (!ptf->fmt.format[ptf->fmt.i] && *ptf->fmt.format)
	{
		ft_printf_buff_cat(ptf, (char*)ptf->fmt.format, ptf->fmt.i);
	}
	return (ptf->buff.read);
}

static void		init_struct(t_ptf *ptf, const char * restrict format)
{
	char *buff;

	buff = ptf->buff.buff;
	ft_bzero(buff, FT_PRINTF_BUFF_SIZE + 1);
	ptf->buff.pos = 0;
	ptf->buff.read = 0;
	ptf->fmt.format = format;
	ptf->fmt.i = 0;
}

int			ft_vprintf(const char * restrict format, va_list ap)
{
	long long		ret;
	t_ptf			ptf;

	init_struct(&ptf, format);
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
