/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_float.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 18:44:17 by bopopovi          #+#    #+#             */
/*   Updated: 2018/07/28 21:29:05 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			treat_arg_type_dbl(t_ptf *ptf, long long param)
{
	char	tmp[MAX_INT_LEN + 56];
	int		size;

	ft_bzero(tmp, MAX_INT_LEN + 1 + (PRECISION >= 0 ? PRECISION : 6));
	size = 0;
	if (ft_strchr("fF", SPECIF))
		ft_ftoa(param, (PRECISION >= 0 ? PRECISION : 6), tmp);
	size = ft_strlen(tmp);
	//get_width_and_precision(buff, 'f', size);
	return (print_arg(ptf, (int*)"\0", (int*)tmp, size));
}

