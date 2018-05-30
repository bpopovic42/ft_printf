/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 15:26:54 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/30 18:10:18 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_printf(const char * restrict format, ...)
{
	t_list		*args;
	va_list		ap;
	char		*line;
	size_t		line_size;
	char		*ptr;

	ptr = (char*)format;
	va_start(ap, format);
	line_size = parse_input(&line, ap, ptr);
	ft_putendl(line);
	ft_putnbr(line_size);
	ft_putchar('\n');
	write(1, line, line_size);
	//args = store_args(format, ap);
	(void)args;
	return (0);
}

size_t		parse_input(char **output, va_list ap, char *format)
{
	size_t	i_size;
	size_t	out_size;

	i_size = 0;
	out_size = 0;
	while (*format && format[i_size])
	{
		if (format[i_size] == '%')
		{
			if ((fast_append(output, format, &out_size, i_size)) < 0)
				return 1; //ERROR
			format += i_size;
			i_size = 0;
			ft_putendl(*output);
			if ((parse_format(output, format, ap, &i_size, &out_size)) < 0)
				return 1; //ERROR
			format += i_size;
			i_size = -1;
			ft_putendl(*output);
		}
		i_size++;
	}
	return (out_size);
}

int		parse_format(char **output, char *format, va_list ap, size_t *i_size, size_t *out_size)
{
	(void)ap;
	(void)format;
	if ((fast_append(output, "#FORMAT#", out_size, 8)) < 0)
		return (-1);
	*i_size += 2;
	return (0);
}

int		fast_append(char **dst, char *app, size_t *dlen, size_t alen)
{
	char *new;

	if (*dst == NULL && alen != 0)
		*dst = ft_strndup(app, alen);
	else
	{
		if (!(new = ft_strnew(*dlen + alen)))
			return (-1);
		if (*dst != NULL && *dlen > 0)
		{
			new = ft_strncpy(new, *dst, *dlen);
			ft_strdel(dst);
		}
		if (app != NULL && app > 0)
			new = ft_strncat(new, app, alen);
		*dst = new;
		new = NULL;
	}
	*dlen += alen;
	return ((int)(*dlen));
}

t_list		*store_args(const char * restrict format, va_list ap)
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
