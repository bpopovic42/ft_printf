/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 19:10:37 by bopopovi          #+#    #+#             */
/*   Updated: 2018/08/17 19:31:55 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		write_intpart(uint64_t val, char *buff, int size)
{
	if (val >= 10)
		size = write_intpart(val / 10, buff, size + 1);
	ft_ccat(buff, val % 10 + '0');
	return (size);
}

static char		*calc_dbl(t_dbl dbl, int precision, char *buff)
{
	int tmp;

	buff[0] = dbl.bits.sign ? '-' : buff[0];
	dbl.bits.sign = 0;
	write_intpart((uint64_t)dbl.val, buff, 1);
	ft_ccat(buff, precision ? '.' : '\0');
	dbl.val -= (uint64_t)dbl.val;
	while (precision)
	{
		dbl.val *= 10;
		tmp = (int)dbl.val;
		dbl.val -= tmp;
		if (precision == 1)
		{
			dbl.val *= 10;
			if ((int)dbl.val >= 5)
				tmp += tmp < 9 ? 1 : 0;
		}
		ft_ccat(buff, tmp + '0');
		precision--;
	}
	return (buff);
}

static char		*is_finite(t_dbl dbl, char *buff)
{
	if (dbl.bits.mant)
		ft_strcat(buff, "nan");
	else
	{
		ft_strcat(buff, "-");
		ft_strcat(buff, "inf");
	}
	return (buff);
}

char			*ft_dtoa(double val, int precision, char *buff)
{
	t_dbl		dbl;

	dbl.val = val;
	if (dbl.bits.expn == 2047)
		return (is_finite(dbl, buff));
	return (calc_dbl(dbl, precision, buff));
}
