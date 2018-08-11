/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_get_flags.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 19:03:18 by bopopovi          #+#    #+#             */
/*   Updated: 2018/08/11 02:54:00 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*get_base(int specifier)
{
	if (ft_strchr("dDiuU", specifier))
		return (DENARY);
	else if (ft_strchr("oO", specifier))
		return (OCTAL);
	else if (ft_strchr("xXp", specifier))
		return (specifier == 'X' ? HEXA_UP : HEXA);
	else
		return (NULL);
}

static void		init_flags(t_ptf *ptf)
{
	WIDTH = 0;
	PRECISION = -1;
	SPEC = 0;
	ft_bzero(FLAGS, 11);
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
	while (FMT[i] && ft_printf_is_flag(FMT[i]) && !ft_printf_is_spec(FMT[i]))
	{
		if (FMT[i] == '.')
			i += get_precision(ap, FMT + i + 1, &(PRECISION)) + 1;
		else if ((ft_strchr("123456789", FMT[i]) || FMT[i] == '*'))
			i += get_width(ap, FMT + i, &(WIDTH), FLAGS);
		else
			ft_strncat(FLAGS, &FMT[i], 1);
		i++;
	}
	if (FMT[i] == '\0')
		return (0);
	SPEC = FMT[i];
	if (ft_strchr("DOUCS", SPEC) && !ft_strchr(FLAGS, 'l'))
		ft_strncat(FLAGS, "l", 1);
	if (SPEC == 's' && ft_strchr(FLAGS, 'l'))
		SPEC = ft_toupper(SPEC);
	if (ft_strchr("dDioOuUxXp", SPEC))
		ptf->base = get_base(SPEC);
	return (i);
}
