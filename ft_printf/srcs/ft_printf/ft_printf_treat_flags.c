/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_treat_flags.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 19:03:18 by bopopovi          #+#    #+#             */
/*   Updated: 2018/07/31 01:13:23 by bopopovi         ###   ########.fr       */
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
	SPECIF = 0;
	ft_bzero(FLAGS, 11);
}

static int	get_width(va_list ap, const char *fmt, int *wd, char *flg)
{
	int i;

	i = 0;
	if (fmt[i] == '*')
	{
		*wd = va_arg(ap, long long);
		if (*wd < 0)
		{
			ft_strncat(flg, (const char*)&"-", 1);
			*wd *= -1;
		}
	}
	else
		i += ft_printf_atoi(fmt, (int*)(wd)) - 1;
	return (i);
}

static int	get_precision(va_list ap, const char *fmt, int *precision)
{
	int i;

	i = 0;
	if (fmt[i] == '*')
		*precision = va_arg(ap, long long);
	else
		i += ft_printf_atoi(fmt, (int*)(precision)) - 1;
	return (i);
}

int			ft_printf_get_flags(t_ptf *ptf, va_list ap, int i)
{
	init_flags(ptf);
	while (FMT[i] && ft_printf_is_flag(FMT[i]) && !ft_printf_is_fspecif(FMT[i]))
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
	SPECIF = FMT[i];
	if (ft_strchr("DOUCS", SPECIF) && !ft_strchr(FLAGS, 'l'))
		ft_strncat(FLAGS, "l", 1);
	if (SPECIF == 's' && ft_strchr(FLAGS, 'l'))
		SPECIF = ft_toupper(SPECIF);
	if (ft_strchr("dDioOuUxXp", SPECIF))
		ptf->base = get_base(SPECIF);
	return (i);
}
