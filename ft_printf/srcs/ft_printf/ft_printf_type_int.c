/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_type_int.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 18:44:17 by bopopovi          #+#    #+#             */
/*   Updated: 2018/09/03 19:18:50 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					get_arg_unsigned(t_ptf *ptf, char *res, long long param)
{
	if (ptf->spec == 'p')
		return (ft_printf_itoa_base(res, ptf->base, (unsigned long long)param));
	else if (ft_strchrn(ptf->flags, 'l') == 2)
		return (ft_printf_uitoa_base(res, ptf->base, (uint64_t)param));
	else if (ft_strchr(ptf->flags, 'l'))
		return (ft_printf_uitoa_base(res, ptf->base, (unsigned long)param));
	else if (ft_strchr(ptf->flags, 'j'))
		return (ft_printf_uitoa_base(res, ptf->base, (uintmax_t)param));
	else if (ft_strchr(ptf->flags, 'z'))
		return (ft_printf_uitoa_base(res, ptf->base, (size_t)param));
	else if (ft_strchrn(ptf->flags, 'h') == 2)
		return (ft_printf_uitoa_base(res, ptf->base, (unsigned char)param));
	else if (ft_strchr(ptf->flags, 'h'))
		return (ft_printf_uitoa_base(res, ptf->base, (unsigned short)param));
	else
		return (ft_printf_uitoa_base(res, ptf->base, (unsigned)param));
}

int					get_arg_signed(t_ptf *ptf, char *res, long long param)
{
	if (ft_strchrn(ptf->flags, 'l') == 2)
		return (ft_printf_itoa_base(res, ptf->base, (long long)param));
	else if (ft_strchr(ptf->flags, 'l'))
		return (ft_printf_itoa_base(res, ptf->base, (long)param));
	else if (ft_strchr(ptf->flags, 'j'))
		return (ft_printf_itoa_base(res, ptf->base, (intmax_t)param));
	else if (ft_strchr(ptf->flags, 'z'))
		return (ft_printf_itoa_base(res, ptf->base, (signed long)param));
	else if (ft_strchrn(ptf->flags, 'h') == 2)
		return (ft_printf_itoa_base(res, ptf->base, (char)param));
	else if (ft_strchr(ptf->flags, 'h'))
		return (ft_printf_itoa_base(res, ptf->base, (short)param));
	else
		return (ft_printf_itoa_base(res, ptf->base, (int)param));
}

static int			get_prefix(t_ptf *ptf, char *ptr, char *prefix)
{
	if (ft_strchr("bBdDi", ptf->spec))
	{
		if (ft_strchr(ptf->flags, '+') || (ptr[0] == '-'))
			ft_strcat(prefix, ptr[0] == '-' ? "-" : "+");
		else if (ft_strchr("dDi", ptf->spec) && ft_strchr(ptf->flags, ' '))
			ft_strcat(prefix, " ");
	}
	if (ft_strchr(ptf->flags, '#') && ft_strchr("xX", ptf->spec))
	{
		if (ptr[1] != '0')
			ft_strcat(prefix, ptf->spec == 'X' ? "0X" : "0x");
	}
	else if (ptf->spec == 'p')
		ft_strcat(prefix, "0x");
	else if (ptf->spec == 'b' || ptf->spec == 'B')
		ft_strcat(prefix, ptf->spec == 'b' ? "0b" : "0B");
	return (ft_strlen(prefix));
}

int					ft_printf_type_int(t_ptf *ptf, long long param)
{
	char	ptr[65];
	char	prefix[5];
	int		size;
	int		htag;

	ft_bzero(prefix, 5);
	htag = ft_strchr(ptf->flags, '#') ? 1 : 0;
	if (ft_strchr("bBdDi", ptf->spec))
		size = get_arg_signed(ptf, ptr, param);
	else
		size = get_arg_unsigned(ptf, ptr, param);
	get_prefix(ptf, ptr, prefix);
	if (!param && !ptf->precision && !(ft_toupper(ptf->spec) == 'O' && htag))
		return (ft_printf_print_arg(ptf, prefix, NULL, 0));
	if (ptf->precision > (int)(size))
		ptf->precision -= size;
	else
		ptf->precision = ptf->precision < 0 ? -1 : 0;
	if (ptf->precision < 1 && ft_toupper(ptf->spec) == 'O' && htag)
		ft_strcat(prefix, ptr[1] == '0' ? "" : "0");
	ptf->width -= (ptf->width > 0) ? ft_strlen(prefix) + size : 0;
	ptf->width -= (ptf->width > 0) && ptf->precision > 0 ? ptf->precision : 0;
	if (ft_toupper(ptf->spec) == 'B' && ptf->precision < 0)
		ptf->precision = 8 - (size % 8 > 0 ? size % 8 : 8);
	return (ft_printf_print_arg(ptf, prefix, (ptr + 1), size));
}
