/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_itoa_base.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 19:52:34 by bopopovi          #+#    #+#             */
/*   Updated: 2018/07/17 14:46:37 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_printf_itoa_base(char *buff, char *charset, uint64_t nbr)
{
	int		base;
	int		i;

	i = 0;
	base = ft_strlen(charset);
	if (base > 16 || base < 2)
		return (-1);
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
