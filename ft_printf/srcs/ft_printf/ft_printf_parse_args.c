/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse_args.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 18:44:17 by bopopovi          #+#    #+#             */
/*   Updated: 2018/06/29 19:08:13 by bopopovi         ###   ########.fr       */
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
		size = print_arg(buff, ptr, ft_strlen(ptr));
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

	size = 1;
	ft_bzero(ptr, 19);
	if (buff->flags.precision && buff->flags.zero)
		buff->flags.zero = 0;
	if (type == 'd' || type == 'i' || type == 'D')
		size = ft_printf_itoa(ptr, va_arg(ap, int64_t));
	else if (type == 'u' || type == 'U')
		size = ft_printf_itoa(ptr, va_arg(ap, int64_t));
	else if (type == 'c')
		ptr[0] = va_arg(ap, int);
	return (print_arg(buff, ptr, size));
}

int			treat_arg_type_base(t_buff *buff, char type, va_list ap)
{
	char	ptr[65];
	int		size;

	size = 0;
	ft_bzero(ptr, 65);
	if (type == 'p')
		size = ft_printf_itoa_base(ptr, 16, va_arg(ap, int64_t));
	else if (type == 'o')
		size = ft_printf_itoa_base(ptr, 8, va_arg(ap, int64_t));
	else if (type == 'O')
		size = ft_printf_itoa_base(ptr, 8, va_arg(ap, int64_t));
	else if (type == 'x')
		size = ft_printf_itoa_base(ptr, 16, va_arg(ap, int64_t));
	else if (type == 'X')
		size = ft_printf_itoa_base(ptr, 16, va_arg(ap, int64_t));
	if (ft_strchr("xX", buff->flags.specifier) && buff->flags.htag && buff->flags.width >= 2 && size && ptr[0] != '0')
		buff->flags.width -= 2;
	return (print_arg(buff, ptr, size));
}

int			print_arg(t_buff *buff, char *input, int size)
{
	int		added_size;
	int		i;

	added_size = 0;
	i = 0;
	if (buff->flags.htag && size >= 1 && input[0] != '0' && ft_strchr("xX", buff->flags.specifier))
		buff->flags.specifier == 'x' ? buff_append(buff, "0x", 2) : buff_append(buff, "0X", 2);
	else if (buff->flags.htag && ft_strchr("oO", buff->flags.specifier) && !buff->flags.precision)
		buff->flags.precision++;
	if (!buff->flags.minus)
		added_size = treat_precision(buff, size);
	if (buff->flags.specifier == 'X')
	{
		while (input[i])
		{
			input[i] = ft_toupper(input[i]);
			i++;
		}
	}
	buff_append(buff, input, size);
	if (buff->flags.htag && ft_strchr("aAeEfFgG", buff->flags.specifier) && !ft_strchr(input, '.'))
		buff_append(buff, ".", 1);
	if (buff->flags.minus)
		added_size = treat_precision(buff, size);
	return (added_size + size + (ft_strchr("xX", buff->flags.specifier) && buff->flags.htag ? 2 : 0));
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
