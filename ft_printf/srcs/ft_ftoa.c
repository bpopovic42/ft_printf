/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 19:10:37 by bopopovi          #+#    #+#             */
/*   Updated: 2018/06/19 20:16:03 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#include <stdio.h>

int		round_it(uint64_t *int_part, char *ftoi, int j);
void	ft_app(char *s, char c);
int		ft_u64toa(uint64_t val, char *buff, int size);

char	*ft_ftoa(double val, int precision, char *buff)
{
	char tab[precision];
	uint64_t int_part;
	int i;

	i = 0;
	buff[0] = val < 0 ? '-' : buff[0];
	val = val < 0 ? val *= -1 : val;
	int_part = (uint64_t)val;
	val -= (uint64_t)val;
	while (i < precision)
	{
		val *= 10;
		tab[i] = (uint64_t)val;
		val -= (uint64_t)val;
		i++;
	}
	if ((val * 10) > 5)
		round_it(&int_part, tab, precision - 1);
	ft_u64toa(int_part, buff, 1);
	if (precision)
		ft_app(buff, '.');
	i = -1;
	while (++i < precision)
		ft_app(buff, tab[i] + '0');
	return (buff);
}

int		round_it(uint64_t *int_part, char *ftoi, int j)
{
	if (j >= 0)
		ftoi[j] += 1;
	else
		int_part[0]++;
	while (j >= 0)
	{
		if (ftoi[j] >= 10)
		{
			ftoi[j] = 0;
			if (j > 0)
				ftoi[j - 1]++;
			else
				int_part[0]++;
		}
		j--;
	}
	return (0);
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
