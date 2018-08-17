/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_float.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 18:44:17 by bopopovi          #+#    #+#             */
/*   Updated: 2018/08/17 19:12:44 by bopopovi         ###   ########.fr       */
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

int			ft_printf_type_dbl(t_ptf *ptf, double param)
{
	char	tmp[MAX_INT_LEN + 56];
	int		size;
	char	prefix[5];

	ft_bzero(tmp, MAX_INT_LEN + 56);
	ft_bzero(prefix, 5);
	size = 0;
	if (ft_strchr("fF", ptf->spec))
	{
		if (ptf->precision == 0 && ft_strchr(ptf->flags, '#'))
			ft_dtoa(param, 1, tmp);
		else if (ptf->precision > 55)
			ft_dtoa(param, 55, tmp);
		else
			ft_dtoa(param, (ptf->precision >= 0 ? ptf->precision : 6), tmp);
		if (ft_strstr(tmp, "inf") || ft_strstr(tmp, "nan"))
			ptf->precision = 0;
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

