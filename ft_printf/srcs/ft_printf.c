/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 15:26:54 by bopopovi          #+#    #+#             */
/*   Updated: 2018/06/26 00:22:59 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			parse_input(char *fmt, t_buff *buff, va_list ap);
int			buff_append(t_buff *buff, char *input, int size);
int			treat_arg(t_buff *buff, char **input, va_list ap);
int			ft_strprepc(char *str, char c);
int			is_fspecif(int c);
int			treat_arg_type_int(t_buff *buff, char type, va_list ap);
int			ptf_itoa(char *buff, int64_t val);
int			treat_arg_type_str(t_buff *buff, char type, va_list ap);

int			ft_printf(const char * restrict format, ...)
{
	va_list		ap;
	size_t		line_size;
	char		*ptr;
	t_buff		buff;

	ptr = (char*)format;
	va_start(ap, format);
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

int			treat_arg(t_buff *buff, char **input, va_list ap)
{
	int			i;
	int			size;

	i = 1;
	size = 0;
	if ((*input)[i] == '%')
		buff_append(buff, *input + i, 1);
	else
	{
		while (!is_fspecif((*input)[i]))
			i++;
	}
	if (ft_strchr("sS", (*input)[i]))
		size += treat_arg_type_str(buff, (*input)[i], ap);
	else if (ft_strchr("pdDioOuUxXcC", (*input)[i]))
		size += treat_arg_type_int(buff, (*input)[i], ap);
	*input += i + 1;
	return (size);
}

int			treat_arg_type_str(t_buff *buff, char type, va_list ap)
{
	char	*ptr;
	int		size;

	size = 0;
	if (type == 's')
	{
		ptr = va_arg(ap, char *);
		size = buff_append(buff, ptr, ft_strlen(ptr));
	}
	return (size);
}

int			treat_arg_type_int(t_buff *buff, char type, va_list ap)
{
	char	ptr[19];
	int		size;

	size = 1;
	ft_bzero(ptr, 19);
	if (type == 'd' || type == 'i')
		size = ptf_itoa(ptr, va_arg(ap, int64_t));
	else if (type == 'c')
		ptr[0] = va_arg(ap, int);
	buff_append(buff, ptr, size);
	return (size);
}

void		print_bits(int64_t val)
{
	ft_putendl("BITS :");
	int size;

	size = (sizeof(val) * 8) - 1;
	while (size)
	{
		if ((val >> size))
		{
			ft_putchar('1');
			val ^= ((val >> size) << size);
		}
		else
			ft_putchar('0');
		size--;
	}
	ft_putchar('\n');
}

int			ptf_itoa(char *buff, int64_t val)
{
	int		size;
	int		is_neg;

	size = 0;
	is_neg = val < 0 ? 1 : 0;
	if (val < 0)
	{
		val = ~val;
		size++;
		val++;
	}
	else if (val == 0)
	{
		ft_strcinsert(buff, '0', 0);
		return (1);
	}
	while (val > 0)
	{
		ft_strcinsert(buff, (val % 10) + '0', 0);
		val /= 10;
		size++;
	}
	if (is_neg)
		ft_strcinsert(buff, '-', 0);
	return (size);
}

int			buff_append(t_buff *buff, char *input, int size)
{
	int i;

	i = 0;
	if (buff->pos + size >= BUFF_SIZE)
	{
		write(1, buff->buff, BUFF_SIZE);
		buff->pos = 0;
		ft_bzero(buff->buff, BUFF_SIZE + 1);
	}
	while (i < size)
	{
		buff->buff[buff->pos + i] = input[i];
		i++;
	}
	buff->pos += i;
	return (i);
}

int			is_fspecif(int c)
{
	return (c == 's' || c == 'S' || c == 'p' || c == 'd' || c == 'D' || c == 'i'
			|| c == 'o' || c == 'O' || c == 'u' || c == 'U' || c == 'x'
				|| c == 'X' || c == 'c' || c == 'C');
}

int			get_format_arg(char *format, char **output, va_list ap)
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

void	fill_buffer(t_buff *buff, void *data, size_t size)
{
	size_t i;

	i = 0;
	while (i < size)
	{
		(buff->buff)[buff->pos] = (char)((char*)data)[i];
		buff->pos++;
		i++;
	}
	(buff->buff)[buff->pos] = '\0';
}

void	init_buffer(t_buff *buff)
{
	buff->pos = 0;
	ft_bzero(buff, BUFF_SIZE + 1);
}
