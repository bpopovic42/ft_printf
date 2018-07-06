/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_itoa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 18:47:23 by bopopovi          #+#    #+#             */
/*   Updated: 2018/07/06 14:25:40 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_printf_itoa(char *buff, int64_t val)
{
	int		size;
	int		is_neg;

	size = 0;
	is_neg = val < 0 ? 1 : 0;
	if (val < 0)
	{
		val = (~val);
		if (val != LLONG_MAX)
			val++;
		else
			is_neg++;
		size++;
	}
	else if (val == 0)
	{
		ft_strcinsert(buff, '0', 0);
		return (1);
	}
	while (val > 0)
	{
		ft_strcinsert(buff, (val % 10) + '0', 0);
		val /= 10;
		size++;
	}
	if (is_neg)
	{
		if (is_neg == 2)
			buff[size - 2]++;
		ft_strcinsert(buff, '-', 0);
	}
	return (size);
}
