/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_type_n.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 17:05:27 by bopopovi          #+#    #+#             */
/*   Updated: 2018/08/30 17:06:00 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf_type_n(t_ptf *ptf, int *n)
{
	ft_printf_dump_fmt(ptf);
	*n = (int)(ptf->buff.read + ptf->buff.pos + ptf->fmt.i);
	return (1);
}
