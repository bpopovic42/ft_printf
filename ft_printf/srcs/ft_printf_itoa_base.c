/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_itoa_base.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 19:52:34 by bopopovi          #+#    #+#             */
/*   Updated: 2018/06/26 20:26:45 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_printf_itoa_base(char *buff, int base, int64_t nbr)
{
	char	*charset = "0123456789abcdef";
	int		i;

	ft_bzero(buff, 64 + 1);
	i = 0;
	if (base > 16 || base < 2)
		return (-1);
	while (nbr)
	{
		buff[i] = charset[nbr % base];
		i++;
		nbr /= base;
	}
	buff = ft_strrev(buff);
	return (i);
}
