/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_treat_flags.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 19:03:18 by bopopovi          #+#    #+#             */
/*   Updated: 2018/07/29 21:51:28 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*get_base(int specifier)
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

int			get_flags(t_ptf *ptf, int i)
{
	WIDTH = 0;
	PRECISION = -1;
	SPECIF = 0;
	ft_bzero(FLAGS, 12);
	while (FMT[i] && !ft_printf_is_fspecif(FMT[i]))
	{
		if (!ft_printf_is_flag(FMT[i]))
			return (i - 1);
		else if (FMT[i] == '.')
			i += ft_printf_atoi(FMT + i + 1, (int*)&(PRECISION));
		else if (ft_strchr("123456789", FMT[i]) && !WIDTH)
			i += ft_printf_atoi(FMT + i, (int*)&(WIDTH)) - 1;
		else
				ft_strncat(FLAGS, &FMT[i], 1);
		i++;
	}
	SPECIF = FMT[i];
	if (ft_strchr("DOUCS", SPECIF) && !ft_strchr(FLAGS, 'l'))
		ft_strncat(FLAGS, "l", 1);
	if (SPECIF == 's' && ft_strchr(FLAGS, 'l'))
		SPECIF = ft_toupper(SPECIF);
	if (ft_strchr("dDioOuUxXp", SPECIF))
		ptf->base = get_base(SPECIF);
	return (i);
}
