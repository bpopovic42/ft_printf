/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 19:10:37 by bopopovi          #+#    #+#             */
/*   Updated: 2018/08/22 17:58:46 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		get_decpart(t_dbl *dbl, int precision, char *buff)
{
	int tmp;

	while (precision)
	{
		dbl->val /= 10;
		dbl->val *= 100;
		tmp = (int)dbl->val;
		dbl->val -= tmp;
		if (precision == 1)
		{
			dbl->val *= 10;
			if ((int)dbl->val >= 5)
				tmp += tmp < 9 ? 1 : 0;
		}
		ft_ccat(buff, tmp + '0');
		precision--;
	}
}

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
	}
	else if (*val < 1)
	{
		while (*val < 1)
		{
			*val *= 10;
			i--;
		}
	}
	return (i);
}

static int		get_intpart(t_dbl *dbl, int *precision, char *buff, char spec)
{
	int expn;

	buff[0] = dbl->bits.sign ? '-' : buff[0];
	dbl->bits.sign = 0;
	if (!(ft_toupper(spec) == 'F' && (int)dbl->val == 0))
		expn = adjust(&(dbl->val)) + (ft_strchr("fF", spec) ? 1 : 0);
	else
		expn = 1;
	if ((*precision == 0 || (ft_toupper(spec) == 'G' && *precision == 1)) && (int)(dbl->val * 10) % 10 > 5)
		dbl->val += 0.5;
	if ((spec == 'G' || spec == 'g'))
	{
		if (expn > -4 && expn < *precision)
			*precision -= write_intpart(&dbl->val, buff, *precision < expn ? *precision : expn);
		else
			*precision -= write_intpart(&dbl->val, buff, 1);
	}
	else
		write_intpart(&dbl->val, buff, ft_strchr("fF", spec) ? expn : 1);
	ft_ccat(buff, *precision ? '.' : '\0');
	dbl->val -= (uint64_t)dbl->val;
	return (expn);
}



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

int			ft_dtoa(double val, int precision, char *buff, char spec)
{
	t_dbl		dbl;
	int			expn;

	dbl.val = val;
	if (dbl.bits.expn == 2047)
	{
		if (dbl.bits.mant)
			ft_strcat(buff, "nan");
		else
		{
			if (dbl.bits.sign)
				ft_strcat(buff, "-");
			ft_strcat(buff, "inf");
		}
		return (0);
	}
	expn = get_intpart(&dbl, &precision, buff + 1, spec);
	get_decpart(&dbl, precision, buff + 1);
	if ((int)(dbl.val) % 10 > 5)
		round_dbl(buff);
	return (expn);
}
