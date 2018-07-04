/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_itoa_base.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 19:52:34 by bopopovi          #+#    #+#             */
/*   Updated: 2018/07/04 20:42:26 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_printf_itoa_base(char *buff, int base, uint64_t nbr)
{
	char	*charset = "0123456789abcdef";
	int		i;

	i = 0;
	if (base > 16 || base < 2)
		return (-1);
	//if (nbr < 0)
	//	nbr = ~(nbr) + 1;
	if (!nbr)
	{
		buff[i] = charset[nbr % base];
		i++;
	}
	else
	{
		while (nbr)
		{
			buff[i] = charset[nbr % base];
			i++;
			nbr /= base;
		}
	}
	buff[i] = '\0';
	buff = ft_strrev(buff);
	return (i);
}
