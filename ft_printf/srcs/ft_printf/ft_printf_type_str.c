/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_type_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 18:44:17 by bopopovi          #+#    #+#             */
/*   Updated: 2018/08/29 01:33:56 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_printf_type_str(t_ptf *ptf, wchar_t *param)
{
	int		size;

	size = 0;
	if (!param || !(char*)param)
	{
		param = (wchar_t*)"(null)";
		ptf->spec = 's';
	}
	if (ptf->spec == 's' || ptf->spec == 'r')
	{
		size = ft_strlen((char*)param);
		if (ptf->precision >= 0 && ptf->precision < size)
			size = ptf->precision;
	}
	else
	{
		if (ptf->precision > 0)
			size = ft_wcsnlen((wchar_t*)param, ptf->precision);
		else if (ptf->precision == 0)
			size = 0;
		else
			size = ft_wcslen((wchar_t*)param);
		if (size < 0)
			return (-1);
	}
	ptf->width -= size;
	return (ft_printf_print_arg(ptf, (int*)"\0", (int*)param, size));
}
