/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 19:06:52 by bopopovi          #+#    #+#             */
/*   Updated: 2018/07/31 03:16:36 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		treat_arg_by_type(t_ptf *ptf, va_list ap)
{
	char invalid;

	invalid = SPECIF;
	if (!ft_printf_is_fspecif(SPECIF) || SPECIF == '%')
	{
		SPECIF = SPECIF == '%' ? '%' : 'c';
		if (SPECIF == '%')
		{
			WIDTH--;
			PRECISION = -1;
			return (print_arg(ptf, (int*)"\0", (int*)"%", 1));
		}
		else
			return (treat_arg_type_char(ptf, (wchar_t)invalid));
	}
	else if (ft_strchr("sS", SPECIF))
		return (treat_arg_type_str(ptf, (wchar_t*)va_arg(ap, long long)));
	else if (ft_strchr("cC", SPECIF))
		return (treat_arg_type_char(ptf, (wchar_t)va_arg(ap, long long)));
	else if (ft_strchr("dDioOuUxXp", SPECIF))
		return (treat_arg_type_int(ptf, va_arg(ap, long long)));
	else if (ft_strchr("fF", SPECIF))
		return(treat_arg_type_dbl(ptf, va_arg(ap, double)));
	return (-1);
}

static int			treat_arg(t_ptf *ptf, va_list ap)
{
	int			i;
	int			size;

	i = 1;
	size = 0;
	if ((i = ft_printf_get_flags(ptf, ap, i + INDEX) - INDEX) <= 0)
		return (i);
	size = treat_arg_by_type(ptf, ap);
	FMT += i + 1;
	INDEX = 0;
	return (size);
}

static int			parse_fmt(t_ptf *ptf, va_list ap)
{
	int		ret;

	ret = 0;
	while (*FMT && FMT[INDEX])
	{
		if (FMT[INDEX] == '%' && FMT[INDEX + 1])
		{
			if ((ret = treat_arg(ptf, ap)) <= 0)
				return (ret);
		}
		else if (FMT[INDEX] == '%' && !FMT[INDEX + 1])
		{
			dump_fmt(ptf);
			FMT += INDEX + 1;
			INDEX = 0;
		}
		else
			INDEX++;
	}
	if (!FMT[INDEX] && *FMT)
	{
		buff_append(ptf, (char*)FMT, INDEX);
	}
	return (ptf->buff.read);
}

static void		init_struct(t_ptf *ptf, const char * restrict format)
{
	ft_bzero(ptf->buff.buff, BUFF_SIZE + 1);
	ptf->buff.pos = 0;
	ptf->buff.read = 0;
	FMT = format;
	INDEX = 0;
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
