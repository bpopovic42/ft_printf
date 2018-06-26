/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 15:26:54 by bopopovi          #+#    #+#             */
/*   Updated: 2018/06/26 18:49:17 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_printf(const char * restrict format, ...)
{
	va_list		ap;

	va_start(ap, format);
	return (ft_vprintf(format, ap));
}

int			ft_vprintf(const char * restrict format, va_list ap)
{
	char	*ptr;
	size_t	line_size;
	t_buff	buff;

	ptr = (char*)format;
	ft_bzero(buff.buff, BUFF_SIZE + 1);
	buff.pos = 0;
	line_size = parse_input(ptr, &buff, ap);
	write(1, buff.buff, buff.pos);
	return (line_size);
}

int			parse_input(char *fmt, t_buff *buff, va_list ap)
{
	int		read;

	read = 0;
	while (*fmt)
	{
		if (*fmt != '%')
		{
			buff_append(buff, fmt, 1);
			fmt++;
			read++;
		}
		else
		{
			read += treat_arg(buff, &fmt, ap);
		}
	}
	return (read);
}
