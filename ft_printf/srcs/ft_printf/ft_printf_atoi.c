/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_atoi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 16:18:15 by bopopovi          #+#    #+#             */
/*   Updated: 2018/08/11 02:25:31 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_printf_atoi(const char *str, int *res)
{
	int			flag;
	size_t		i;

	i = 0;
	*res = 0;
	while (ft_isspace(str[i]))
		i++;
	flag = str[i] == '-' ? -1 : 1;
	i += str[i] == '-' || str[i] == '+' ? 1 : 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		*res = (*res * 10) + (str[i++] - '0');
	*res *= flag;
	return (i);
}
