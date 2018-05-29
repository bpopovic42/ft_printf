/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 15:26:54 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/29 17:48:47 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char * restrict format, ...)
{
	t_list		*args;
	va_list		ap;

	va_start(ap, format);
	args = store_args(format, ap);
	return (0);
}

t_list	*store_args(const char * restrict format, va_list ap)
{
	int			d;
	char		c;
	char		*s;

	while (*format)
	{
		if (*format == 's')
		{
			s = va_arg(ap, char *);
			ft_putstr(s);
		}
		else if (*format == 'd')
		{
			d = va_arg(ap, int);
			ft_putnbr(d);
		}
		else if (*format == 'c')
		{
			c = va_arg(ap, int);
			ft_putchar(c);
		}
		format++;
	}
	return (NULL);
}
