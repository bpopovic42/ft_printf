/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 19:10:37 by bopopovi          #+#    #+#             */
/*   Updated: 2018/08/21 19:24:38 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		write_intpart(double *val, char *buff, int i)
{
	double test;
	int		ret;

	test = *val;
	ret = 0;
	while (i)
	{
		ft_ccat(buff, (long long)(test) % 10 + '0');
		test -= (long long)(test);
		test /= 10;
		test *= 100;
		*val *= 10;
		if (i < 0)
			i++;
		else
			i--;
		ret++;
	}
	*val /= 10;
	*val -= (long long)*val;
	return (ret);
}

static int		adjust(double *val)
{
	int i;

	i = 0;
	if (*val >= 10)
	{
		while (*val >= 10)
		{
			*val /= 10;
			i++;
		}
		i++;
	}
	else if (*val < 1)
	{
		while (*val < 1)
		{
			*val *= 10;
			i--;
		}
		i--;
	}
	return (i);
}

static void		rounding(t_dbl *dbl, int precision)
{
	int i;

	i = precision;
	while (i)
	{
		dbl->val *= 10;
		i--;
	}
	if ((int)(dbl->val) % 10 > 5)
		dbl->val += 5;
	while (i < precision)
	{
		dbl->val /= 10;
		i++;
	}
}

static int		calc_dbl(t_dbl dbl, int precision, char *buff, char spec)
{
	int tmp;
	int expn;

	buff[0] = dbl.bits.sign ? '-' : buff[0];
	dbl.bits.sign = 0;
	if (!(ft_toupper(spec) == 'F' && (int)dbl.val == 0))
		expn = adjust(&(dbl.val));
	else
		expn = 1;
	if (precision < 6)
		rounding(&dbl, precision);
	if ((spec == 'G' || spec == 'g'))
	{
		if (expn > -4 && expn < precision)
			precision -= write_intpart(&dbl.val, buff, precision < expn ? precision : expn);
		else
			precision -= write_intpart(&dbl.val, buff, 1);
	}
	else if ((spec == 'F' || spec == 'f'))
		write_intpart(&dbl.val, buff, expn);
	else if ((spec == 'E' || spec == 'e'))
		write_intpart(&dbl.val, buff, 1);
	ft_ccat(buff, precision ? '.' : '\0');
	dbl.val -= (uint64_t)dbl.val;
	while (precision)
	{
		dbl.val /= 10;
		dbl.val *= 100;
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
	return (expn < 0 ? expn - 1 : expn + 1);
}

static char		*is_finite(t_dbl dbl, char *buff)
{
	if (dbl.bits.mant)
		ft_strcat(buff, "nan");
	else
	{
		if (dbl.bits.sign)
			ft_strcat(buff, "-");
		ft_strcat(buff, "inf");
	}
	return (buff);
}

int			ft_dtoa(double val, int precision, char *buff, char spec)
{
	t_dbl		dbl;
	int			expn;

	dbl.val = val;
	if (dbl.bits.expn == 2047)
	{
		is_finite(dbl, buff);
		return (0);
	}
	expn = calc_dbl(dbl, precision, buff, spec);
	return (expn);
}
