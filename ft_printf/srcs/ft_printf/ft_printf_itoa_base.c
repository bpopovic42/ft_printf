/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_itoa_base.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 19:52:34 by bopopovi          #+#    #+#             */
/*   Updated: 2018/07/30 17:19:09 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_printf_itoa_base(char *buff, char *charset, long long nbr)
{
	int		base;
	int		i;
	char	*ptr;
	int		max;

	i = 0;
	max = nbr == LLONG_MIN ? 1 : 0;
	ptr = buff;
	base = ft_strlen(charset);
	*ptr = nbr < 0 ? '-' : '+';
	nbr = nbr == LLONG_MIN ? 9223372036854775807 : nbr;
	nbr *= nbr < 0 ? -1 : 1;
	if (base > 16 || base < 2 || !ptr)
		return (-1);
	ptr++;
	while (nbr || i < 1)
	{
		ptr[i] = charset[nbr % base];
		i++;
		nbr /= base;
	}
	ptr[0] += max;
	ptr[i] = '\0';
	ptr = ft_strrev(ptr);
	return (i);
}
