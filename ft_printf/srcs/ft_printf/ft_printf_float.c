/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_float.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 18:44:17 by bopopovi          #+#    #+#             */
/*   Updated: 2018/08/22 19:51:10 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			get_prefix(t_ptf *ptf, char *ptr, char *prefix)
{
	if (ft_strchr(ptf->flags, '+'))
		ft_strcat(prefix, ptr[0] == '-' ? "" : "+");
	else if (ft_strchr(ptf->flags, ' '))
		ft_strcat(prefix, " ");
}

static void			get_suffix(char *suffix, char spec, int expn)
{
	int min;

	min = 0;
	if (expn < 0)
	{
		expn = -expn;
		min = 1;
	}
	if (expn)
	{
		while (expn)
		{
			ft_ccat(suffix, expn % 10 + '0');
			expn /= 10;
		}
	}
	else
		ft_strcat(suffix, "00");
	ft_ccat(suffix, ft_strlen(suffix) == 1 ? '0' : '\0');
	ft_ccat(suffix, min ? '-' : '+');
	ft_ccat(suffix, spec);
	suffix = ft_strrev(suffix);
}

static void			get_arg(t_ptf *ptf, double param, char *tmp, char *suffix)
{
	int		expn;
	int		i;

	if ((ft_strchr(ptf->flags, '#') || ft_strchr("gG", ptf->spec)))
		ptf->precision = !ptf->precision ? 1 : ptf->precision;
	if (ptf->precision > MAX_DBL_PRECISION)
		expn = ft_dtoa(param, MAX_DBL_PRECISION, tmp, ptf->spec);
	else if (ptf->precision < 0)
		expn = ft_dtoa(param, 6, tmp, ptf->spec);
	else
		expn = ft_dtoa(param, ptf->precision, tmp, ptf->spec);
	tmp = !tmp[0] ? ft_strcpy(tmp, tmp + 1) : tmp;
	i = ft_strlen(tmp);
	while (tmp[i--] == '0')
		i--;
	if (ft_strchr("gG", ptf->spec))
	{
		tmp[tmp[i] == '.' ? i : i + 1] = '\0';
		if (expn < -4 || (expn > ptf->precision && ptf->precision != 0))
			ptf->spec = ptf->spec == 'G' ? 'E' : 'e';
	}
	if (ft_strstr(tmp, "inf") || ft_strstr(tmp, "nan"))
		ptf->precision = 0;
	else if (ft_strchr("eE", ptf->spec))
		get_suffix(suffix, ft_isupper(ptf->spec) ? 'E' : 'e', expn);
	tmp[2] = ft_strchr(ptf->flags, '#') && ptf->precision == 0 ? '\0' : tmp[2];
}

int			ft_printf_type_dbl(t_ptf *ptf, double param)
{
	char	tmp[MAX_DBL_LEN + MAX_DBL_PRECISION + 1];
	int		size;
	char	prefix[5];
	char	suffix[7];
	int		ret;

	ft_bzero(tmp, MAX_DBL_LEN + MAX_DBL_PRECISION + 1);
	ft_bzero(prefix, 5);
	ft_bzero(suffix, 7);
	size = 0;
	ret = 0;
	get_arg(ptf, param, tmp, suffix);
	get_prefix(ptf, tmp, prefix);
	size = ft_strlen(tmp);
	if (ptf->precision > MAX_DBL_PRECISION)
		ptf->precision -= MAX_DBL_PRECISION;
	else
		ptf->precision = 0;
	ptf->width -= size + ft_strlen(prefix) + ft_strlen(suffix);
	ret = ft_printf_print_arg(ptf, (int*)prefix, (int*)tmp, size);
	ft_printf_buff_cat(ptf, suffix, ft_strlen(suffix));
	return (ret);
}

