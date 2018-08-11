/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 18:44:17 by bopopovi          #+#    #+#             */
/*   Updated: 2018/08/11 03:14:44 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_printf_type_char(t_ptf *ptf, wchar_t param)
{
	char	mbs[5];
	int		size;

	ft_bzero(mbs, 5);
	size = 1;
	if (ft_strchr(FLAGS, 'l'))
	{
		if (param && (size = ft_wctomb((unsigned char*)mbs, param)) < 0)
			return (-1);
	}
	else
		*mbs = (char)param;
	WIDTH -= size;
	return (ft_printf_print_arg(ptf, (int*)"\0", (int*)mbs, size));
}


