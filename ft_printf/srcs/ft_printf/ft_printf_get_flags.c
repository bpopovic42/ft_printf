/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_get_flags.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 19:03:18 by bopopovi          #+#    #+#             */
/*   Updated: 2018/08/12 18:25:29 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char inline		*get_base(int spec)
{
	if (ft_strchr("dDiuU", spec))
		return (BASE_DENARY);
	else if (spec == 'o' || spec == 'O')
		return (BASE_OCTAL);
	else if (spec == 'p' || spec == 'x' || spec == 'X')
		return (spec == 'X' ? BASE_HEXA_UP : BASE_HEXA);
	else
		return (NULL);
}

static void inline		init_flags(t_ptf *ptf)
{
	ptf->width = 0;
	ptf->precision = -1;
	ptf->spec = 0;
	ft_bzero(ptf->flags, 11);
}

static int	get_width(va_list ap, const char *fmt, int *width, char *flg)
{
	int i;

	i = 0;
	if (fmt[i] == '*')
	{
		*width = va_arg(ap, int);
		if (*width < 0)
		{
			ft_strncat(flg, (const char*)&"-", 1);
			*width *= -1;
		}
	}
	else
		i += ft_printf_atoi(fmt, width) - 1;
	return (i);
}

static int	get_precision(va_list ap, const char *fmt, int *precision)
{
	int i;

	i = 0;
	if (fmt[i] == '*')
		*precision = va_arg(ap, int);
	else
		i += ft_printf_atoi(fmt, precision) - 1;
	return (i);
}

int			ft_printf_get_flags(t_ptf *ptf, va_list ap, int i)
{
	const char *fmt;
	char *flags;

	init_flags(ptf);
	fmt = ptf->fmt.format;
	flags = ptf->flags;
	while (fmt[i] && ft_printf_is_flag(fmt[i]))
	{
		if (fmt[i] == '.')
			i += get_precision(ap, fmt + i + 1, &(ptf->precision)) + 1;
		else if (ft_strchr("123456789*", fmt[i]))
			i += get_width(ap, fmt + i, &(ptf->width), flags);
		else if ((ft_strchrn(flags, (int)fmt[i])) < 2)
			ft_strncat(flags, &fmt[i], 1);
		i++;
	}
	ptf->spec = fmt[i];
	ptf->base = get_base(ptf->spec);
	if (ft_strchr("DOUCS", ptf->spec) && !ft_strchr(flags, 'l'))
		ft_strncat(flags, "l", 1);
	if (ptf->spec == 's' && ft_strchr(flags, 'l'))
		ptf->spec = 'S';
	return (i);
}
