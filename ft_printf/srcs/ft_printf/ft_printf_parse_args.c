/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse_args.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 18:44:17 by bopopovi          #+#    #+#             */
/*   Updated: 2018/07/04 21:26:31 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			treat_arg_type_str(t_buff *buff, char type, va_list ap)
{
	char	*ptr;
	wchar_t	*wptr;
	int		size;

	size = 0;
	if (type == 's')
	{
		ptr = va_arg(ap, char *);
		if (!ptr)
			ptr = "(null)";
		size = print_arg(buff, ptr, ptr ? ft_strlen(ptr) : 0);
	}
	else if (type == 'S')
	{
		wptr = va_arg(ap, wchar_t *);
		size = treat_arg_type_wcstr(buff, wptr, ft_wcslen(wptr));
	}
	return (size);
}

int			treat_arg_type_wcstr(t_buff *buff, wchar_t *wcstr, size_t size)
{
	char	ptr[size * sizeof(wchar_t) + 1];
	size_t	bytes;

	ft_bzero(ptr, size * sizeof(wchar_t) + 1);
	bytes = ft_wcstombs(ptr, wcstr, size * sizeof(wchar_t));
	return (print_arg(buff, ptr, bytes));
}

int			treat_arg_type_int(t_buff *buff, char type, va_list ap)
{
	char	ptr[19];
	int		size;
	int64_t		tmp;

	size = 1;
	ft_bzero(ptr, 19);
	if (buff->flags.l == 'l')
		tmp = va_arg(ap, long);
	else if (buff->flags.l == 'L')
		tmp = va_arg(ap, long long);
	else if (buff->flags.j)
		tmp = va_arg(ap, intmax_t);
	else if (buff->flags.z)
		tmp = va_arg(ap, size_t);
	else
		tmp = va_arg(ap, int);
	if (buff->flags.precision > 0 && buff->flags.zero)
		buff->flags.zero = 0;
	if (type == 'd' || type == 'i' || type == 'D')
		size = ft_printf_itoa(ptr, tmp);
	else if (type == 'u' || type == 'U')
		size = ft_printf_itoa(ptr, tmp);
	else if (type == 'c')
		ptr[0] = tmp;
	return (print_arg(buff, ptr, size));
}

int			treat_arg_type_base(t_buff *buff, char type, va_list ap)
{
	char	ptr[65];
	int		size;
	uint64_t	tmp;

	size = 0;
	ft_bzero(ptr, 65);
	if (buff->flags.l == 'l')
		tmp = va_arg(ap, unsigned long);
	else if (buff->flags.l == 'L')
		tmp = va_arg(ap, unsigned long long);
	else if (buff->flags.j)
		tmp = va_arg(ap, uintmax_t);
	else if (buff->flags.z)
		tmp = va_arg(ap, size_t);
	else
		tmp = va_arg(ap, unsigned int);
	if (type == 'p')
		size = ft_printf_itoa_base(ptr, 16, tmp);
	else if (type == 'o' || type == 'O')
		size = ft_printf_itoa_base(ptr, 8, tmp);
	else if (type == 'x' || type == 'X')
		size = ft_printf_itoa_base(ptr, 16, tmp);
	if (ft_strchr("xX", buff->flags.specifier) && buff->flags.htag && buff->flags.width >= 2 && size && ptr[0] != '0')
		buff->flags.width -= 2;
	return (print_arg(buff, ptr, size));
}

int			treat_arg_type_dbl(t_buff *buff, char type, va_list ap)
{
	char	tmp[MAX_INT_LEN + 1 + buff->flags.precision]; // + precision
	int		size;

	ft_bzero(tmp, MAX_INT_LEN + 1);
	size = 0;
	if (type == 'f')
	{
		ft_ftoa(va_arg(ap, double), buff->flags.precision ? buff->flags.precision : 6, tmp);
		size = ft_strlen(tmp);
	}
	return (print_arg(buff, tmp, size));
}

void		util_printf_flags(t_buff *buff)
{
	printf("htag : %d, zero : %d, minus : %d, space : %d, plus : %d, apos : %d, width : %d, precision : %d\n",
		buff->flags.htag, buff->flags.zero, buff->flags.minus, buff->flags.space, buff->flags.plus,
			buff->flags.apos, buff->flags.width, buff->flags.precision);
}

int			print_arg(t_buff *buff, char *input, int size)
{
	int		added_size;
	int		i;

	added_size = 0;
	i = 0;

	if (ft_strchr("aAdeEfFgG", buff->flags.specifier) && ((buff->flags.zero && buff->flags.width > 0) || (buff->flags.precision > size)))
	{
		if (buff->flags.plus && *input != '-')
		{
			added_size++;
			buff->flags.width -= buff_append(buff, "+", 1);
		}
		else if (*input == '-')
		{
			input++;
			added_size++;
			size--;
			buff->flags.width -= buff_append(buff, "-", 1);
		}
		buff->flags.plus = 0;
	}

	if (buff->flags.htag && ft_strchr("oO", buff->flags.specifier) && buff->flags.width > 0)
		buff->flags.width--;

	if (size > 0 && buff->flags.precision >= 0 && buff->flags.specifier == 's')
	{
		input[buff->flags.precision] = '\0';
		size = buff->flags.precision;
	}

	if (!buff->flags.minus)
	{
		if (buff->flags.specifier == 'c' && !*input && buff->flags.width > 0)
			size = 1;
		if (buff->flags.specifier == 'c' && !*input && buff->flags.width <= 0)
			buff->flags.precision = 0;
		added_size += treat_precision(buff, input, size);
	}

	if (buff->flags.specifier == 'X')
	{
		while (input[i])
		{
			input[i] = ft_toupper(input[i]);
			i++;
		}
	}

	if (buff->flags.htag && size >= 1 && input[0] != '0' && ft_strchr("xX", buff->flags.specifier) && !buff->flags.zero)
		buff->flags.specifier == 'x' ? buff_append(buff, "0x", 2) : buff_append(buff, "0X", 2);

	if (buff->flags.htag && ft_strchr("oO", buff->flags.specifier))
		added_size += buff_append(buff, "0", 1);

	size = !buff->flags.precision && input[0] == '0' ? 0 : size;

	if (buff->flags.precision > size && ft_strchr("dioOuUxX", buff->flags.specifier))
	{
		while ((buff->flags.precision - size) > 0)
		{
			buff_append(buff, ft_strchr("dioOuUxX", buff->flags.specifier) ? "0" : " ", 1);
			buff->flags.precision--;
			added_size++;
			buff->flags.width--;
		}
	}

	if (ft_strchr("aAdeEfFgGi", buff->flags.specifier) && (buff->flags.space || buff->flags.plus))
	{
		if (buff->flags.plus && *input != '-')
			added_size += buff_append(buff, "+", 1);
		else if (buff->flags.space && *input != '-')
			added_size += buff_append(buff, " ", 1);
	}

	if ((input && *input) || buff->flags.specifier == 'c')
		size = buff_append(buff, input, size < buff->flags.precision || buff->flags.precision < 1  || !ft_strchr("sS", buff->flags.specifier) ? size : buff->flags.precision);

	if (buff->flags.htag && ft_strchr("aAeEfFgG", buff->flags.specifier) && !ft_strchr(input, '.'))
		buff_append(buff, ".", 1);

	if (buff->flags.minus)
		added_size += treat_precision(buff, input, size);

	return (added_size + size + (ft_strchr("xX", buff->flags.specifier) && buff->flags.htag && input[0] != '0' ? 2 : 0));
}
