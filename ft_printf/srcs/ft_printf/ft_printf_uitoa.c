/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_uitoa.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 18:47:23 by bopopovi          #+#    #+#             */
/*   Updated: 2018/07/06 14:45:29 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_printf_uitoa(char *buff, uint64_t val)
{
	int		size;

	size = 0;
	while (val > 0)
	{
		ft_strcinsert(buff, (val % 10) + '0', 0);
		val /= 10;
		size++;
	}
	return (size);
}
