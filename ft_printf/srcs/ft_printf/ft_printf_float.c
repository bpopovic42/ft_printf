/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_float.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 18:44:17 by bopopovi          #+#    #+#             */
/*   Updated: 2018/08/11 00:27:48 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int			get_prefix(t_ptf *ptf, char *ptr, char *prefix)
{
	if (ft_strchr(FLAGS, '+'))
		ft_strcat(prefix, ptr[0] == '-' ? "" : "+");
	else if (ft_strchr(FLAGS, ' '))
		ft_strcat(prefix, " ");
	return (ft_strlen(prefix));
}

int			treat_arg_type_dbl(t_ptf *ptf, double param)
{
	char	tmp[MAX_INT_LEN + 56];
	int		size;
	char	prefix[5];

	ft_bzero(tmp, MAX_INT_LEN + 56);
	ft_bzero(prefix, 5);
	size = 0;
	if (ft_strchr("fF", SPEC))
	{
		if (PRECISION == 0 && ft_strchr(FLAGS, '#'))
			ft_ftoa(param, 1, tmp);
		else if (PRECISION > 55)
			ft_ftoa(param, 55, tmp);
		else
			ft_ftoa(param, (PRECISION >= 0 ? PRECISION : 6), tmp);
	}
	if (ft_strchr(FLAGS, '#') && PRECISION == 0)
		tmp[2] = '\0';
	get_prefix(ptf, tmp, prefix);
	size = ft_strlen(tmp);
	if (PRECISION > 55)
		PRECISION -= 55;
	else
		PRECISION = 0;
	WIDTH -= size + ft_strlen(prefix);
	return (ft_printf_print_arg(ptf, (int*)prefix, (int*)tmp, size));
}

