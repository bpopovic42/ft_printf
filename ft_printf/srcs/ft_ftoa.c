/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 19:10:37 by bopopovi          #+#    #+#             */
/*   Updated: 2018/06/13 20:29:46 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_app(char *s, char c);

char	*ft_ftoa(double val, int precision, char *buff)
{
	unsigned long long int		int_part;
	int		i;

	i = 0;
	int_part = (int)val;
	val -= int_part;
	ft_strcat(buff, ft_itoa(int_part));
	ft_app(buff, '.');
	while (i < precision)
	{
		val *= 10;
		ft_app(buff, (char)((int)val + '0'));
		val -= (int)val;
		i++;
	}
	return (buff);
}

void	ft_app(char *s, char c)
{
	while (*s)
		s++;
	*s = c;
}
