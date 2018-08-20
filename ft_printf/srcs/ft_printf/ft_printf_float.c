/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_float.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 18:44:17 by bopopovi          #+#    #+#             */
/*   Updated: 2018/08/20 20:48:25 by bopopovi         ###   ########.fr       */
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
	unsigned int expn;
	t_dbl		test;

	ft_bzero(tmp, MAX_DBL_LEN + MAX_DBL_PRECISION + 1);
	ft_bzero(prefix, 5);
	ft_bzero(suffix, 7);
	size = 0;
	dbl.val = param;
	ret = 0;
	suffix_size = 0;
	expn = 0;
	test.val = param;
	int exp_res = 0;
	while (test.val < 1 || test.val > 9)
	{
		if (test.val < 1)
		{
			test.val *= 10;
			exp_res++;
		}
		else if (test.val > 9)
		{
			test.val /= 10;
			exp_res--;
		}
	}
	if (ft_strchr("gG", ptf->spec))
	{
		if (ptf->precision == 0)
			ptf->precision = 1;
		if (exp_res < -4 || exp_res >= ptf->precision)
			ptf->spec = ptf->spec == 'G' ? 'E' : 'e';
		else
			ptf->spec = ptf->spec == 'G' ? 'F' : 'f';
	}
	if (ft_strchr("fF", ptf->spec))
	{
		if (ptf->precision == 0 && ft_strchr(ptf->flags, '#'))
			ft_dtoa(param, 1, tmp);
		else if (ptf->precision > MAX_DBL_PRECISION)
			ft_dtoa(param, MAX_DBL_PRECISION, tmp);
		else
			ft_dtoa(param, (ptf->precision >= 0 ? ptf->precision : 6), tmp);
		if (ft_strstr(tmp, "inf") || ft_strstr(tmp, "nan"))
			ptf->precision = 0;
	}
	else if (ft_strchr("eE", ptf->spec))
	{
		if (ptf->precision == 0 && ft_strchr(ptf->flags, '#'))
			expn = ft_dtoas(param, 1, tmp);
		else if (ptf->precision > MAX_DBL_PRECISION)
			expn = ft_dtoas(param, MAX_DBL_PRECISION, tmp);
		else
			expn = ft_dtoas(param, (ptf->precision >= 0 ? ptf->precision : 6), tmp);
		if (ft_strstr(tmp, "inf") || ft_strstr(tmp, "nan"))
			ptf->precision = 0;
		if (ft_strstr(tmp, "inf") || ft_strstr(tmp, "nan"))
			ptf->precision = 0;
		else
			suffix_size = get_suffix(suffix, ptf->spec, (int)expn);
	}
	if (ft_strchr(ptf->flags, '#') && ptf->precision == 0)
		tmp[2] = '\0';
	get_prefix(ptf, tmp, prefix);
	size = ft_strlen(tmp);
	if (ptf->precision > MAX_DBL_PRECISION)
		ptf->precision -= MAX_DBL_PRECISION;
	else
		ptf->precision = 0;
	ptf->width -= size + ft_strlen(prefix);
	ret = ft_printf_print_arg(ptf, (int*)prefix, ft_strchr("EF", ptf->spec)  ? (int*)ft_strtoupper(tmp) : (int*)tmp, size);
	ft_printf_buff_cat(ptf, suffix, suffix_size);
	return (ret);
}

