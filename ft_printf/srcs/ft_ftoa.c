/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 19:10:37 by bopopovi          #+#    #+#             */
/*   Updated: 2018/06/18 18:05:39 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#include <stdio.h>

int		round_it_up(uint64_t *ftoi, int j);
void	ft_app(char *s, char c);
int		ft_u64toa(uint64_t val, char *buff, int size);

/*char	*ft_ftoa(double val, int precision, char *buff)
{
	uint64_t	int_part;
	int			radix;
	int			i;

	i = 0;
	radix = 0;
	if (val < 0)
	{
		buff[0] = '-';
		radix++;
		i++;
		val *= -1;
	}
	while (val >= 10 && val >= 1)
	{
		val /= 10;
		radix++;
	}
	int_part = (int)val;
	val -= int_part;
	int_part *= 10;
	buff[radix + 1] = '.';
	while (i < precision + radix + 1)
	{
		val *= 10;
		int_part += (int)val;
		if (i + 1 != precision)
			int_part *= 10;
		val -= (int)val;
		i++;
	}
	if (int_part % 10 > 5)
		int_part++;
	int_part /= 10;
	//i++;
	while (i >= 0)
	{
		if (buff[i] != '.' && buff[i] != '-')
		{
			buff[i] = int_part % 10 + '0';
			int_part /= 10;
		}
		i--;
	}
	//printf("%llu", int_part);
	return (buff);
}*/

char	*ft_ftoa(double val, int precision, char *buff)
{
	uint64_t	ftoi[(precision / 18) + 1];
	int			i;
	int			j;

	i = 0;
	j = 0;
	if (val < 0)
	{
		buff[0] = '-';
		val *= -1;
	}
	ftoi[j] = (uint64_t)val;
	val -= ftoi[j];
	while (precision > 0)
	{
		if (precision % 18 == 0 || j == 0)
			ftoi[++j] = 0;
		val *= 10;
		if ((uint64_t)val == 0 && ftoi[j] == 0)
			break;
		ftoi[j] = (ftoi[j] * 10) + (uint64_t)val;
		val -= (uint64_t)val;
		precision--;
	}
	if ((val * 10) > 5)
	{
		precision += round_it_up(ftoi, j);
	}
	j++;
	while (i < j)
	{
		ft_u64toa(ftoi[i], buff, 1);
		if (j == 1)
			break;
		if (i == 0)
			ft_app(buff, '.');
		i++;
	}
	while (precision > 1)
	{
		ft_app(buff, '0');
		precision--;
	}
	ft_app(buff, '\0');
	return (buff);
}

int		round_it_up(uint64_t *ftoi, int j)
{
	uint64_t tmp;
	uint64_t pow;
	int i;

	tmp = 0;
	i = 0;
	pow = 1;
	while (ftoi[j] % 10 == 9)
	{
		tmp += (ftoi[j] % 10) * pow;
		ftoi[j] /= 10;
		i++;
		pow *= 10;
	}
	if (ftoi[j] != 0)
	{
		while (ftoi[j] != 0)
		{
			tmp += (ftoi[j] % 10) * pow;
			ftoi[j] /= 10;
			pow *= 10;
		}
		ftoi[j] = tmp + 1;
		return (0);
	}
	else
	{
		if (j > 0)
		{
			ftoi[j] = 0;
			i += round_it_up(ftoi, j - 1);
		}
	}
	return (i);
}

int		ft_u64toa(uint64_t val, char *buff, int size)
{
	if (val >= 10)
		size = ft_u64toa(val / 10, buff, size + 1);
	ft_app(buff, val % 10 + '0');
	return (size);
}

void	ft_app(char *s, char c)
{
	while (*s)
		s++;
	*s = c;
}
