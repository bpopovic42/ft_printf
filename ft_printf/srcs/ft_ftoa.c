/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 19:10:37 by bopopovi          #+#    #+#             */
/*   Updated: 2018/06/19 14:58:40 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#include <stdio.h>

int		round_it_up(uint64_t *ftoi, int j);
void	ft_app(char *s, char c);
int		ft_u64toa(uint64_t val, char *buff, int size);

char	*ft_ftoa(double val, int precision, char *buff)
{
	uint64_t	ftoi[(precision / 18) + 2]; // Max nbr of char - 1 for LLONG_MAX
	int			i;
	int			j;

	i = 0;
	j = 0;
	buff[0] = val < 0 ? '-' : buff[0];
	val = val < 0 ? val *= -1 : val;
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
		precision += round_it_up(ftoi, j);
	j++;
	ft_u64toa(ftoi[0], buff, 1);
	ft_app(buff, '.');
	while (++i < j)
		ft_u64toa(ftoi[i], buff, 1);
	while (precision-- > 1)
		ft_app(buff, '0');
	ft_app(buff, '\0');
	return (buff);
}

int		round_it_up(uint64_t *ftoi, int j)
{
	uint64_t tmp;
	uint64_t pow;
	int i;

	tmp = 0;
	pow = 1;
	i = 0;
	while (ftoi[j] % 10 == 9)
	{
		tmp += (ftoi[j] % 10) * pow;
		ftoi[j] /= 10;
		pow *= 10;
		i++;
	}
	if (ftoi[j] != 0)
	{
		ftoi[j] *= (pow / 10);
		ftoi[j] += tmp + 1;
		return (0);
	}
	else if (j > 0)
		i += round_it_up(ftoi, j - 1);
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
