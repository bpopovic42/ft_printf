/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 19:06:52 by bopopovi          #+#    #+#             */
/*   Updated: 2018/07/30 17:32:51 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_vprintf(const char * restrict format, va_list ap)
{
	int		line_size;
	t_ptf	ptf;

	init_struct(&ptf, format);
	line_size = parse_input(&ptf, ap);
	if (ptf.buff.pos != 0 && line_size >= 0)
		line_size += write(1, ptf.buff.buff, ptf.buff.pos);
	return (line_size);
}

int			init_struct(t_ptf *ptf, const char * restrict format)
{
	ft_bzero(ptf->buff.buff, BUFF_SIZE + 1);
	ptf->buff.pos = 0;
	ptf->buff.read = 0;
	FMT = format;
	INDEX = 0;
	return (1);
}

int			parse_input(t_ptf *ptf, va_list ap)
{
	int		ret;

	ret = 0;
	while (*FMT && FMT[INDEX])
	{
		if (FMT[INDEX] == '%')
		{
			if ((ret = treat_arg(ptf, ap)) < 0)
				return (-1);
			else if (ret == 0)
				return (0);
		}
		else
			INDEX++;
	}
	if (!FMT[INDEX] && *FMT)
		ptf->buff.read += write(1, FMT, INDEX);
	return (ptf->buff.read);
}

int			treat_arg(t_ptf *ptf, va_list ap)
{
	int			i;
	int			size;

	i = 1;
	size = 0;
	i = get_flags(ptf, i + INDEX) - INDEX;
	if (i <= 0)
		return (i);
	if (ft_strchr("fFeEgGaA", SPECIF))
		size = treat_arg_type_dbl(ptf, va_arg(ap, double));
	else
		size = treat_specifier_by_type(ptf, (!ft_printf_is_fspecif(SPECIF) || SPECIF == '%' ? 0 : va_arg(ap, long long)));
	FMT += i + 1;
	INDEX = 0;
	return (size);
}

int		treat_specifier_by_type(t_ptf *ptf, long long param)
{
	char invalid;

	invalid = 0;
	if (ft_strchr("sS", SPECIF))
		return (treat_arg_type_str(ptf, (wchar_t*)param));
	else if (ft_strchr("cC", SPECIF))
		return (treat_arg_type_char(ptf, (wchar_t)param));
	else if (ft_strchr("dDioOuUxXp", SPECIF))
		return (treat_arg_type_int(ptf, param));
	else if (SPECIF == '%')
	{
		WIDTH--;
		PRECISION = -1;
		return(print_arg(ptf, (int*)"\0", (int*)"%", 1));
	}
	else
	{
		invalid = SPECIF;
		SPECIF = 'c';
		return (treat_arg_type_char(ptf, (wchar_t)invalid));
	}
	return (-1);
}
