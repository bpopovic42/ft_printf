/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_get_flags.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 19:03:18 by bopopovi          #+#    #+#             */
/*   Updated: 2018/08/11 03:44:49 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*get_base(int specifier)
{
	if (ft_strchr("dDiuU", specifier))
		return (BASE_DENARY);
	else if (ft_strchr("oO", specifier))
		return (BASE_OCTAL);
	else if (ft_strchr("xXp", specifier))
		return (specifier == 'X' ? BASE_HEXA_UP : BASE_HEXA);
	else
		return (NULL);
}

static void		init_flags(t_ptf *ptf)
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
	init_flags(ptf);
	while (ptf->fmt.format[i] && ft_printf_is_flag(ptf->fmt.format[i]) && !ft_printf_is_spec(ptf->fmt.format[i]))
	{
		if (ptf->fmt.format[i] == '.')
			i += get_precision(ap, ptf->fmt.format + i + 1, &(ptf->precision)) + 1;
		else if ((ft_strchr("123456789", ptf->fmt.format[i]) || ptf->fmt.format[i] == '*'))
			i += get_width(ap, ptf->fmt.format + i, &(ptf->width), ptf->flags);
		else
			ft_strncat(ptf->flags, &ptf->fmt.format[i], 1);
		i++;
	}
	if (ptf->fmt.format[i] == '\0')
		return (0);
	ptf->spec = ptf->fmt.format[i];
	if (ft_strchr("DOUCS", ptf->spec) && !ft_strchr(ptf->flags, 'l'))
		ft_strncat(ptf->flags, "l", 1);
	if (ptf->spec == 's' && ft_strchr(ptf->flags, 'l'))
		ptf->spec = ft_toupper(ptf->spec);
	if (ft_strchr("dDioOuUxXp", ptf->spec))
		ptf->base = get_base(ptf->spec);
	return (i);
}
