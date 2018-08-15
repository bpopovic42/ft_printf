/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_float.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 18:44:17 by bopopovi          #+#    #+#             */
/*   Updated: 2018/08/15 19:29:40 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int			get_prefix(t_ptf *ptf, char *ptr, char *prefix)
{
	if (ft_strchr(ptf->flags, '+'))
		ft_strcat(prefix, ptr[0] == '-' ? "" : "+");
	else if (ft_strchr(ptf->flags, ' '))
		ft_strcat(prefix, " ");
	return (ft_strlen(prefix));
}

static int			is_spec_dbl(double param, char *buf)
{
	t_flt	tmp;

	tmp.nbr = param;
	if (tmp.bits.expn == 2047 && tmp.bits.mant == 0)
	{
		if (tmp.bits.sign == 0)
			buf = "inf";
		else
			buf = "-inf";
		return (1);
	}
	else if (tmp.bits.expn == 2047 && tmp.bits.mant != 0)
	{
		buf = "NaN";
		return (1);
	}
	else if (tmp.bits.expn == 0 && tmp.bits.mant == 0)
	{
		if (tmp.bits.sign == 0)
			buf = "0";
		else
			buf = "-0";
		return (1);
	}
	return (0);
}

int			ft_printf_type_dbl(t_ptf *ptf, double param)
{
	char	tmp[MAX_INT_LEN + 56];
	int		size;
	char	prefix[5];

	ft_bzero(tmp, MAX_INT_LEN + 56);
	ft_bzero(prefix, 5);
	size = 0;
	if (is_spec_dbl(param, tmp))
		return (ft_printf_print_arg(ptf, (int*)prefix, (int*)tmp, size));
	if (ft_strchr("fF", ptf->spec))
	{
		if (ptf->precision == 0 && ft_strchr(ptf->flags, '#'))
			ft_ftoa(param, 1, tmp);
		else if (ptf->precision > 55)
			ft_ftoa(param, 55, tmp);
		else
			ft_ftoa(param, (ptf->precision >= 0 ? ptf->precision : 6), tmp);
	}
	if (ft_strchr(ptf->flags, '#') && ptf->precision == 0)
		tmp[2] = '\0';
	get_prefix(ptf, tmp, prefix);
	size = ft_strlen(tmp);
	if (ptf->precision > 55)
		ptf->precision -= 55;
	else
		ptf->precision = 0;
	ptf->width -= size + ft_strlen(prefix);
	return (ft_printf_print_arg(ptf, (int*)prefix, (int*)tmp, size));
}

