/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 18:44:17 by bopopovi          #+#    #+#             */
/*   Updated: 2018/08/11 00:27:31 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			treat_arg_type_str(t_ptf *ptf, wchar_t *param)
{
	int		size;

	size = 0;
	if (!param || !(char*)param)
	{
		param = (wchar_t*)"(null)";
		SPEC = 's';
	}
	if (SPEC == 's')
	{
		size = ft_strlen((char*)param);
		if (PRECISION >= 0 && PRECISION < size)
			size = PRECISION;
	}
	else
	{
		if (PRECISION > 0)
			size = ft_wcsnlen((wchar_t*)param, PRECISION);
		else if (PRECISION == 0)
			size = 0;
		else
			size = ft_wcslen((wchar_t*)param);
		if (size < 0)
			return (-1);
	}
	WIDTH -= size;
	return (ft_printf_print_arg(ptf, (int*)"\0", (int*)param, size));
}
