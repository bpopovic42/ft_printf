/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_type_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 18:44:17 by bopopovi          #+#    #+#             */
/*   Updated: 2018/09/04 17:56:07 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_printf_type_str(t_ptf *ptf, wchar_t *param)
{
	int		size;

	size = 0;
	ptf->spec = (!param || !(char*)param) ? 's' : ptf->spec;
	param = (!param || !(char*)param) ? (wchar_t*)"(null)" : param;
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
	ft_printf_print_arg(ptf, "\0", (char*)param, size);
	return (1);
}
