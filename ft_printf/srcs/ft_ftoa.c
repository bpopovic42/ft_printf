/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 19:10:37 by bopopovi          #+#    #+#             */
/*   Updated: 2018/06/14 22:55:36 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#include <stdio.h>

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
	uint64_t	int_part;
	uint64_t	dec_part;
	int			i;

	i = 0;
	if (val < 0)
	{
		buff[0] = '-';
		i++;
		val *= -1;
	}
	int_part = (uint64_t)val;
	val -= int_part;
	i += ft_u64toa(int_part, buff, 1);
	buff[i] = '.';
	i++;
	while (precision > 0)
	{
		val *= 10;
		if ((int)val == 0)
		{
			buff[i] = '0';
		}
		precision--;
		i++;
	}
	dec_part = (uint64_t)val;
	if (dec_part % 10 >= 5)
		dec_part++;
	ft_u64toa(dec_part, buff, 1);
	return (buff);
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
