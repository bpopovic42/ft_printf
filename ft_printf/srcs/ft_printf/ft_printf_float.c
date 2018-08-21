/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_float.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 18:44:17 by bopopovi          #+#    #+#             */
/*   Updated: 2018/08/21 20:16:10 by bopopovi         ###   ########.fr       */
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

static int			get_suffix(char *suffix, char spec, int expn)
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
	return (ft_strlen(suffix));
}

int			ft_printf_type_dbl(t_ptf *ptf, double param)
{
	char	tmp[MAX_DBL_LEN + MAX_DBL_PRECISION + 1];
	int		size;
	char	prefix[5];
	char	suffix[7];
	t_dbl	dbl;
	int		ret;
	int		suffix_size;
	int expn;
	int			i;

	ft_bzero(tmp, MAX_DBL_LEN + MAX_DBL_PRECISION + 1);
	ft_bzero(prefix, 5);
	ft_bzero(suffix, 7);
	size = 0;
	dbl.val = param;
	ret = 0;
	suffix_size = 0;
	expn = 0;
	i = 0;
	if (ft_strchr("gG", ptf->spec))
		ptf->precision = ptf->precision == 0 ? 1 : ptf->precision;
	if (ptf->precision == 0 && ft_strchr(ptf->flags, '#'))
		expn = ft_dtoa(param, 1, tmp, ptf->spec);
	else if (ptf->precision > MAX_DBL_PRECISION)
		expn = ft_dtoa(param, MAX_DBL_PRECISION, tmp, ptf->spec);
	else
		expn = ft_dtoa(param, (ptf->precision >= 0 ? ptf->precision : 6), tmp, ptf->spec);
	if (ft_strchr("gG", ptf->spec))
	{
		i = ft_strlen(tmp) - 1;
		while (tmp[i] == '0')
			i--;
		tmp[tmp[i] == '.' ? i : i + 1] = '\0';
	}
	if (ft_strstr(tmp, "inf") || ft_strstr(tmp, "nan"))
		ptf->precision = 0;
	else if (ptf->spec == 'e' || ptf->spec == 'E' || (ft_strchr("gG", ptf->spec) && (expn < -4 || (expn > ptf->precision && ptf->precision != 0))))
		suffix_size = get_suffix(suffix, ft_isupper(ptf->spec) ? 'E' : 'e', (int)expn);
	if (ft_strchr(ptf->flags, '#') && ptf->precision == 0)
		tmp[2] = '\0';
	get_prefix(ptf, tmp, prefix);
	size = ft_strlen(tmp);
	if (ptf->precision > MAX_DBL_PRECISION)
		ptf->precision -= MAX_DBL_PRECISION;
	else
		ptf->precision = 0;
	ptf->width -= size + ft_strlen(prefix);
	ret = ft_printf_print_arg(ptf, (int*)prefix, ft_strchr("EFG", ptf->spec) ? (int*)ft_strtoupper(tmp) : (int*)tmp, size);
	ft_printf_buff_cat(ptf, suffix, suffix_size);
	return (ret);
}

