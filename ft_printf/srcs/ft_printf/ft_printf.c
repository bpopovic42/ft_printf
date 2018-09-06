/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 15:26:54 by bopopovi          #+#    #+#             */
/*   Updated: 2018/09/06 17:35:34 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Printf version including 'aAcCdDeEfFgGinoOpsSuUxX' standard conversions
** Non standard conversions are :
** 'bB' for binary and 'r' for non-printable strings (octal form)
** Flags implemented :
** '-+# .hjlz*'
** Include a color format handling (refer to ft_printf.h for details)
** This printf version uses no malloc
*/

int			ft_printf(const char *restrict format, ...)
{
	va_list		ap;
	int			ret;

	va_start(ap, format);
	ret = ft_vprintf(format, ap);
	va_end(ap);
	return (ret);
}
