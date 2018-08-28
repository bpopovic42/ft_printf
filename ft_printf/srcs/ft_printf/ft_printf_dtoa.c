/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_dtoa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 19:10:37 by bopopovi          #+#    #+#             */
/*   Updated: 2018/08/28 19:20:51 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void round_dbl(char *buff)
{
	int i;

	i = ft_strlen(buff + 1);
	while (i)
	{
		if (buff[i] == '9')
			buff[i] = '0';
		else if (buff[i] != '.')
		{
			if (i == 0)
				buff[i] = '1';
			else
				buff[i]++;
			break;
		}
		i--;
	}
}

static int		dtoa_base(double *val, char *buff, int i, char *bstr)
{
	double	tmp;
	int		ret;
	int		base;

	tmp = *val;
	ret = 0;
	base = ft_strlen(bstr);
	while (i)
	{
		ft_ccat(buff, bstr[(long long)(tmp)]);
		tmp -= (long long)(tmp);
		tmp /= base;
		tmp *= (base * base);
		*val *= base;
		if (i < 0)
			i++;
		else
			i--;
		ret++;
	}
	*val /= base;
	*val -= (long long)*val;
	return (ret);
}

static int		adjust(double *val, char spec)
{
	int i;
	int base;

	i = 0;
	base = ft_toupper(spec) == 'A' ? 2 : 10;
	if (*val > (ft_toupper(spec) == 'A' ? 1 : 9) || *val < 1)
	{
		while ((int)*val > (ft_toupper(spec) == 'A' ? 1 : 9) || (int)*val < 1)
		{
			if (*val > (ft_toupper(spec) == 'A' ? 1 : 9))
			{
				*val /= base;
				i++;
			}
			else
			{
				*val *= base;
				i--;
			}
		}
	}
	return (i);
}


static int		getint(t_dbl *dbl, int *prec, char *buff, char spec, char *bstr)
{
	int expn;
	int base;
	int intpart_size;

	base = ft_strlen(bstr);
	buff[0] = dbl->bits.sign ? '-' : buff[0];
	dbl->bits.sign = 0;
	intpart_size = 0;
	if (!(ft_toupper(spec) == 'F' && (int)dbl->val == 0))
		expn = adjust(&(dbl->val), spec) + (ft_strchr("fF", spec) ? 1 : 0);
	else
		expn = 1;
	if ((spec == 'G' || spec == 'g') || (spec == 'a' || spec == 'A'))
	{
		if (expn > -4 && expn < *prec && expn != 0 && ft_toupper(spec) != 'A')
			intpart_size = dtoa_base(&dbl->val, buff, expn, bstr);
		else
			intpart_size = dtoa_base(&dbl->val, buff, 1, bstr);
		*prec -= (spec == 'G' || spec == 'g' ? intpart_size : 0);
	}
	else
		dtoa_base(&dbl->val, buff, ft_strchr("fF", spec) ? expn : 1, bstr);
	ft_ccat(buff, *prec ? '.' : '\0');
	dbl->val -= (long long)dbl->val;
	return (expn);
}

#include <stdio.h>

int			ft_printf_dtoa(double val, int prec, char *buff, char spec)
{
	t_dbl		dbl;
	int			expn;
	int			base;
	char		*bstr;

	dbl.val = val;
	bstr = BASE_DENARY;
	if (spec == 'a' || spec == 'A')
		bstr = spec == 'A' ? BASE_HEXA_UP : BASE_HEXA;
	base = ft_strlen(bstr);
	if (dbl.bits.expn == 2047)
	{
		ft_strcat(buff, dbl.bits.mant ? "nan" : "\0");
		if (!dbl.bits.mant)
			ft_strcat(buff, dbl.bits.sign ? "-inf" : "inf");
		buff = ft_isupper(spec) ? ft_strtoupper(buff) : buff;
		return (0);
	}
	expn = getint(&dbl, &prec, buff + 1, spec, bstr);
	dbl.val *= base;
	dtoa_base(&dbl.val, buff + 1, prec, bstr);
	if ((int)(dbl.val) > (base / 2))
		round_dbl(buff);
	return (expn);
}
