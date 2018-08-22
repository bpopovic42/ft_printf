/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 19:10:37 by bopopovi          #+#    #+#             */
/*   Updated: 2018/08/22 18:23:52 by bopopovi         ###   ########.fr       */
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

static int		write_intpart(double *val, char *buff, int i)
{
	double	tmp;
	int		ret;

	tmp = *val;
	ret = 0;
	while (i)
	{
		ft_ccat(buff, (long long)(tmp) % 10 + '0');
		tmp -= (long long)(tmp);
		tmp /= 10;
		tmp *= 100;
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
	if (*val > 9 || *val < 1)
	{
		while (*val > 9 || *val < 1)
		{
			if (*val > 9)
			{
				*val /= 10;
				i++;
			}
			else
			{
				*val *= 10;
				i--;
			}
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
	dbl->val -= (long long)dbl->val;
	return (expn);
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
			ft_strcat(buff, dbl.bits.sign ? "-inf" : "inf");
		return (0);
	}
	expn = get_intpart(&dbl, &precision, buff + 1, spec);
	while (precision)
	{
		dbl.val /= 10;
		dbl.val *= 100;
		ft_ccat(buff + 1, (int)dbl.val + '0');
		dbl.val -= (int)dbl.val;
		precision--;
	}
	if ((int)(dbl.val * 10) % 10 > 5)
		round_dbl(buff);
	return (expn);
}
