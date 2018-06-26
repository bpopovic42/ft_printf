/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 15:26:54 by bopopovi          #+#    #+#             */
/*   Updated: 2018/06/26 17:38:08 by bopopovi         ###   ########.fr       */
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
		while (!ft_printf_is_fspecif((*input)[i]))
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
		size = ft_printf_itoa(ptr, va_arg(ap, int64_t));
	else if (type == 'c')
		ptr[0] = va_arg(ap, int);
	buff_append(buff, ptr, size);
	return (size);
}

int			ft_printf_itoa(char *buff, int64_t val)
{
	int		size;
	int		is_neg;

	size = 0;
	is_neg = val < 0 ? 1 : 0;
	if (val < 0)
	{
		val = (~val) + 1;
		size++;
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

int			ft_printf_is_fspecif(int c)
{
	return (c == 's' || c == 'S' || c == 'p' || c == 'd' || c == 'D' || c == 'i'
			|| c == 'o' || c == 'O' || c == 'u' || c == 'U' || c == 'x'
				|| c == 'X' || c == 'c' || c == 'C');
}
