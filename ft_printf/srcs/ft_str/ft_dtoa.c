/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 19:10:37 by bopopovi          #+#    #+#             */
/*   Updated: 2018/08/27 18:34:29 by bopopovi         ###   ########.fr       */
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

static int		write_intpart(double *val, char *buff, int i, char *base_str)
{
	double	tmp;
	int		ret;
	int		base;

	tmp = *val;
	ret = 0;
	base = ft_strlen(base_str);
	while (i)
	{
		ft_ccat(buff, base_str[(long long)(tmp)]);
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


static int		get_intpart(t_dbl *dbl, int *precision, char *buff, char spec, char *base_str)
{
	int expn;
	int base;
	int intpart_size;

	base = ft_strlen(base_str);
	buff[0] = dbl->bits.sign ? '-' : buff[0];
	dbl->bits.sign = 0;
	intpart_size = 0;
	if (!(ft_toupper(spec) == 'F' && (int)dbl->val == 0))
		expn = adjust(&(dbl->val), spec) + (ft_strchr("fF", spec) ? 1 : 0);
	else
		expn = 1;
	if ((spec == 'G' || spec == 'g') || (spec == 'a' || spec == 'A'))
	{
		if (expn > -4 && expn < *precision && expn != 0 && ft_toupper(spec) != 'A')
			intpart_size = write_intpart(&dbl->val, buff, expn, base_str);
		else
			intpart_size = write_intpart(&dbl->val, buff, 1, base_str);
		*precision -= (spec == 'G' || spec == 'g' ? intpart_size : 0);
	}
	else
		write_intpart(&dbl->val, buff, ft_strchr("fF", spec) ? expn : 1, base_str);
	ft_ccat(buff, *precision ? '.' : '\0');
	dbl->val -= (long long)dbl->val;
	return (expn);
}

int			ft_dtoa(double val, int precision, char *buff, char spec)
{
	t_dbl		dbl;
	int			expn;
	int			base;
	char		*base_str;

	dbl.val = val;
	base_str = BASE_DENARY;
	if (spec == 'a' || spec == 'A')
		base_str = spec == 'A' ? BASE_HEXA_UP : BASE_HEXA;
	base = ft_strlen(base_str);
	if (dbl.bits.expn == 2047)
	{
		ft_strcat(buff, dbl.bits.mant ? "nan" : "\0");
		if (!dbl.bits.mant)
			ft_strcat(buff, dbl.bits.sign ? "-inf" : "inf");
		buff = ft_isupper(spec) ? ft_strtoupper(buff) : buff;
		return (0);
	}
	expn = get_intpart(&dbl, &precision, buff + 1, spec, base_str);
	while (precision)
	{
		dbl.val = (dbl.val / base) * (base * base);
		if (((int)dbl.val % base) > base || ((int)dbl.val < 0))
			ft_ccat(buff + 1, (int)dbl.val < 0 ? '0' : (int)dbl.val + '0');
		else
			ft_ccat(buff + 1, base_str[(int)dbl.val]);
		dbl.val -= (int)dbl.val;
		precision--;
	}
	if ((int)(dbl.val * base) % base > (base / 2))
		round_dbl(buff);
	return (expn);
}
