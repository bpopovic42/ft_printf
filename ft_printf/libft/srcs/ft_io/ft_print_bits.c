/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_bits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 17:18:06 by bopopovi          #+#    #+#             */
/*   Updated: 2018/06/26 17:25:02 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_print_bits(int64_t val)
{
	int size;

	size = (sizeof(val) * 8) - 1;
	while (size)
	{
		if ((val >> size))
		{
			ft_putchar('1');
			val ^= ((val >> size) << size);
		}
		else
			ft_putchar('0');
		size--;
	}
}
