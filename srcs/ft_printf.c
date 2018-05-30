/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 15:26:54 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/30 19:46:33 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_printf(const char * restrict format, ...)
{
	va_list		ap;
	char		*line;
	size_t		line_size;
	char		*ptr;

	ptr = (char*)format;
	va_start(ap, format);
	line_size = parse_format_string(&line, ap, ptr);
	write(1, line, line_size);

	return (0);
}

/*
** Reads from the format string (fmt)
** Takes the address of a string for the treated input sections to be appended to
** Returns the total size of final treated output
*/

size_t		parse_format_string(char **output, va_list ap, char *fmt)
{
	size_t	flen;
	size_t	olen;

	flen = 0;
	olen = 0;
	while (*fmt && fmt[flen])
	{
		if (fmt[flen] == '%')
		{
			if ((fast_append(output, &fmt, &olen, &flen)) < 0)
				return 1; //ERROR
			ft_putendl(*output);
			if ((parse_format(output, &fmt, ap, &flen, &olen)) < 0)
				return 1; //ERROR
			ft_putendl(*output);
		}
		flen++;
	}
	return (olen);
}

int		parse_format(char **output, char **format, va_list ap, size_t *in_len, size_t *out_len)
{
	(void)ap;
	(void)format;
	char		*arg;
	size_t		format_len;
	size_t		arg_len;

	format_len = get_format_arg(*format, &arg, ap);
	arg_len = ft_strlen(arg);
	if ((fast_append(output, &arg, out_len, &arg_len)) < 0)
		return (-1);
	*format += format_len;
	return (0);
}

int		is_fspecif(int c)
{
	return (c == 's' || c == 'S' || c == 'p' || c == 'd' || c == 'D' || c == 'i'
			|| c == 'o' || c == 'O' || c == 'u' || c == 'U' || c == 'x'
				|| c == 'X' || c == 'c' || c == 'C');
}

int		get_format_arg(char *format, char **output, va_list ap)
{
	size_t	i;
	int		format_len;
	int		buff;

	i = 1;
	format_len = 0;
	buff = 0;
	while (!is_fspecif(format[i]))
		i++;
	format_len = (int)i;
	if (format[format_len] == 'd')
	{
		buff = va_arg(ap, int);
		*output = ft_itoa(buff);
	}
	else
		*output = ft_strdup("#Unsupported specifier");
	return (format_len + 1);
}

int		fast_append(char **dst, char **app, size_t *dlen, size_t *alen)
{
	char *new;

	if (*dst == NULL && *alen != 0)
		*dst = ft_strndup(*app, *alen);
	else
	{
		if (!(new = ft_strnew(*dlen + *alen)))
			return (-1);
		if (*dst != NULL && *dlen > 0)
		{
			new = ft_strncpy(new, *dst, *dlen);
		}
		if (app != NULL && *alen > 0)
		{
			new = ft_strncat(new, *app, *alen);
			*app += *alen;
		}
		*dst = new;
		new = NULL;
	}
	*dlen += *alen;
	*alen = 0;
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
