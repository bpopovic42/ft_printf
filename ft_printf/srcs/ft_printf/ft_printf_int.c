/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 18:44:17 by bopopovi          #+#    #+#             */
/*   Updated: 2018/07/30 18:45:24 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		get_arg_unsigned(t_ptf *ptf, char *res, long long param)
{
	if (SPECIF == 'p')
		return(ft_printf_itoa_base(res, ptf->base, (unsigned long long)param));
	else if (ft_strchrn(FLAGS, 'l') == 2)
		return (ft_printf_uitoa_base(res, ptf->base, (uint64_t)param));
	else if (ft_strchr(FLAGS, 'l'))
		return (ft_printf_uitoa_base(res, ptf->base, (unsigned long)param));
	else if (ft_strchrn(FLAGS, 'h') == 2)
		return (ft_printf_uitoa_base(res, ptf->base, (unsigned char)param));
	else if (ft_strchr(FLAGS, 'h'))
		return (ft_printf_uitoa_base(res, ptf->base, (unsigned short)param));
	else if (ft_strchr(FLAGS, 'j'))
		return (ft_printf_uitoa_base(res, ptf->base, (uintmax_t)param));
	else if (ft_strchr(FLAGS, 'z'))
		return (ft_printf_uitoa_base(res, ptf->base, (size_t)param));
	else
		return (ft_printf_uitoa_base(res, ptf->base, (unsigned)param));
}

int			get_arg_signed(t_ptf *ptf, char *res, long long param)
{
	if (ft_strchrn(FLAGS, 'l') == 2)
		return (ft_printf_itoa_base(res, ptf->base, (long long)param));
	else if (ft_strchr(FLAGS, 'l'))
		return (ft_printf_itoa_base(res, ptf->base, (long)param));
	else if (ft_strchrn(FLAGS, 'h') == 2)
		return (ft_printf_itoa_base(res, ptf->base, (char)param));
	else if (ft_strchr(FLAGS, 'h'))
		return (ft_printf_itoa_base(res, ptf->base, (short)param));
	else if (ft_strchr(FLAGS, 'j'))
		return (ft_printf_itoa_base(res, ptf->base, (intmax_t)param));
	else if (ft_strchr(FLAGS, 'z'))
		return (ft_printf_itoa_base(res, ptf->base, (signed long)param));
	else
		return (ft_printf_itoa_base(res, ptf->base, (int)param));
}

static int			get_prefix(t_ptf *ptf, char *ptr, char *prefix)
{
	if (ft_strchr("dDi", SPECIF) && (ft_strchr(FLAGS, '+') || (ptr[0] == '-')))
		ft_strcat(prefix, ptr[0] == '-' ? "-" : "+");
	else if (ft_strchr("dDi", SPECIF) && ft_strchr(FLAGS, ' '))
		ft_strcat(prefix, " ");
	if (ft_strchr(FLAGS, '#') && ft_strchr("xX", SPECIF) && *(ptr + 1) != '0')
	{
		if ((SPECIF == 'x' || SPECIF == 'X' || SPECIF == 'p'))
			ft_strcat(prefix, SPECIF == 'X' ? "0X" : "0x");
	}
	else if (SPECIF == 'p')
		ft_strcat(prefix, "0x");
	return (ft_strlen(prefix));
}

int			treat_arg_type_int(t_ptf *ptf, long long param)
{
	char	ptr[65];
	char	prefix[5];
	int				size;

	size = 1;
	ft_bzero(ptr, 65);
	ft_bzero(prefix, 5);
	if (ft_strchr("dDi", SPECIF))
		size = get_arg_signed(ptf, ptr, param);
	else
		size = get_arg_unsigned(ptf, ptr, param);
	get_prefix(ptf, ptr, prefix);
	if (!param && !PRECISION && !(ft_strchr("oO", SPECIF) && ft_strchr(FLAGS, '#')))
		return (print_arg(ptf, (int*)prefix, NULL, 0));
	if (PRECISION > (int)(size))
		PRECISION -= size;
	else
		PRECISION = PRECISION < 0 ? -1 : 0;
	if (PRECISION <= 0 && ft_strchr("oO", SPECIF) && ft_strchr(FLAGS, '#'))
		ft_strcat(prefix, ptr[1] == '0' ? "" : "0");
	if (WIDTH > 0)
		WIDTH -= (PRECISION > 0 ? PRECISION : 0) + ft_strlen(prefix) + size;
	return (print_arg(ptf, (int*)prefix, (int*)(ptr + 1), size));
}
