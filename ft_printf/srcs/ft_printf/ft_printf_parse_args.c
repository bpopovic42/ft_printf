/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse_args.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 18:44:17 by bopopovi          #+#    #+#             */
/*   Updated: 2018/07/18 21:32:06 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long		get_varg(t_buff *buff, char type, va_list ap)
{
	long long value;

	value = 0;
	if (ft_strchr("fFgGeE", type))
		value = va_arg(ap, double);
	else if (ft_strchr("sSuUxXoOp", type))
		value = get_varg_uint(buff, type, ap);
	else if (ft_strchr("dDicC", type))
		value = get_varg_int(buff, type, ap);
	return (value);
}

long long		get_varg_int(t_buff *buff, char type, va_list ap)
{
	long long value;

	value = 0;
	(void)type;
	if (buff->flags.h == 'h')
		value = (short)va_arg(ap, int);
	else if (buff->flags.h == 'H')
		value = (signed char)va_arg(ap, int);
	else if (buff->flags.l == 'l')
		value = va_arg(ap, long);
	else if (buff->flags.l == 'L')
		value = va_arg(ap, long long);
	else if (buff->flags.j)
		value = va_arg(ap, intmax_t);
	else if (buff->flags.z)
		value = va_arg(ap, ssize_t);
	else
		value = va_arg(ap, int);
	return (value);
}

long long		get_varg_uint(t_buff *buff, char type, va_list ap)
{
	long long value;

	value = 0;
	if (buff->flags.h == 'h' && type != 'U')
		value = (unsigned short)va_arg(ap, unsigned);
	else if (buff->flags.h == 'H')
		value = (unsigned char)va_arg(ap, unsigned);
	else if (buff->flags.l == 'l' || ft_strchr("sSU", type))
		value = va_arg(ap, unsigned long);
	else if (buff->flags.l == 'L')
		value = va_arg(ap, unsigned long long);
	else if (buff->flags.j)
		value = va_arg(ap, uintmax_t);
	else if (buff->flags.z)
		value = va_arg(ap, size_t);
	else
		value = va_arg(ap, unsigned int);
	return (value);
}

int			treat_arg_type_str(t_buff *buff, char type, long long value)
{
	int		size;

	size = 0;
	if (type == 's' && buff->flags.l != 'l')
	{
		if (!value)
			value = (unsigned long)&"(null)";
		size = ft_strlen((char*)value);
		if (WIDTH > size)
			WIDTH -= size;
		size = print_arg(buff, (char*)value, size);
	}
	else if (type == 'S' || (type == 's' && buff->flags.l == 'l'))
	{
		if (!value)
			value = (unsigned long)&L"(null)";
		size = ft_wcslen((wchar_t*)value);
		if (WIDTH > size)
			WIDTH -= size;
		size = treat_arg_type_wcstr(buff, (wchar_t*)value, size);
	}
	return (size);
}

int			treat_arg_type_wcstr(t_buff *buff, wchar_t *wcstr, size_t size)
{
	unsigned char	ptr[size * sizeof(wchar_t) + 1];
	size_t			bytes;

	ft_bzero(ptr, size * sizeof(wchar_t) + 1);
	bytes = ft_wcstombs(ptr, wcstr, size * sizeof(wchar_t));
	if (WIDTH > (int)bytes)
		WIDTH -= size;
	return (print_arg(buff, (char*)ptr, bytes));
}

int			treat_arg_type_int(t_buff *buff, char type, long long value)
{
	char	ptr[19];
	int		size;

	size = 1;
	ft_bzero(ptr, 19);
	if (buff->flags.l == 'l' && type == 'c')
		type = 'C';
	if (PRECISION > 0 && ZERO)
		ZERO = 0;
	if (type == 'c')
		ptr[0] = value;
	else if (type == 'C')
	{
		if (!value)
			size = buff_append(buff, "\0", 1);
		else
			size = ft_wctomb((unsigned char*)ptr, value);
	}
	else
		size = ft_printf_itoa((char*)ptr, value);
	if (PRECISION > size)
		PRECISION -= size;
	else
		PRECISION = -1;
	if (WIDTH > size + (PRECISION > 0 ? PRECISION : 0))
		WIDTH -= size + (PRECISION > 0 ? PRECISION : 0);
	else
		WIDTH = 0;
	return (print_arg(buff, ptr, size));
}

int			treat_arg_type_uint(t_buff *buff, char type, long long value)
{
	char	ptr[19];
	int		size;

	(void)type;
	size = 1;
	ft_bzero(ptr, 19);
	if (PRECISION > 0 && ZERO)
		ZERO = 0;
	size = ft_printf_uitoa(ptr, value);
	if (PRECISION > size)
		PRECISION -= size;
	else
		PRECISION = -1;
	if (WIDTH > size + (PRECISION > 0 ? PRECISION : 0))
		WIDTH -= size + (PRECISION > 0 ? PRECISION : 0);
	else
		WIDTH = 0;
	return (print_arg(buff, ptr, size));
}

int			treat_arg_type_base(t_buff *buff, char type, long long value)
{
	char	ptr[65];
	int		size;

	size = 0;
	ft_bzero(ptr, 65);
	size = ft_printf_itoa_base(ptr, ft_strchr("oO", type) ? OCTAL : HEXA, value);
	if (type == 'X')
	{
		int i = 0;
		while (ptr[i])
		{
			ptr[i] = ft_toupper(ptr[i]);
			i++;
		}
	}
	if (ft_strchr("pxX", SPECIF) && HTAG && WIDTH >= 2 && size && ptr[0] != '0')
		WIDTH -= 2;
	if (HTAG && ft_strchr("oO", SPECIF) && WIDTH > 0)
		WIDTH--;
	if (PRECISION > size)
		PRECISION -= size;
	else
		PRECISION = -1;
	if (WIDTH > size + (PRECISION > 0 ? PRECISION : 0))
		WIDTH -= size + (PRECISION > 0 ? PRECISION : 0);
	else
		WIDTH = 0;
	return (print_arg(buff, ptr, size));
}

int			treat_arg_type_dbl(t_buff *buff, char type, long long value)
{
	char	tmp[MAX_INT_LEN + 1 + (PRECISION >= 0 ? PRECISION : 6)]; // + precision
	int		size;

	ft_bzero(tmp, MAX_INT_LEN + 1 + (PRECISION >= 0 ? PRECISION : 6));
	size = 0;
	if (ft_strchr("fF", type))
	{
		ft_ftoa(value, (PRECISION >= 0 ? PRECISION : 6), tmp);
		size = ft_strlen(tmp);
		PRECISION = 0;
	}
	if (WIDTH > size)
		WIDTH -= size;
	else
		WIDTH = 0;
	return (print_arg(buff, tmp, size));
}

int			print_arg(t_buff *buff, char *input, int size)
{
	(void)size;
	if (!MINUS && WIDTH >= 0)
		buff_seqncat(buff, " ", WIDTH);
	input = treat_flag_plus(buff, input);
	treat_htag(buff, input);
	if (PRECISION >= 0)
		buff_seqncat(buff, "0", PRECISION);
	buff_append(buff, input, ft_strlen(input));
	if (MINUS && WIDTH >= 0)
		buff_seqncat(buff, ZERO ? "0" : " ", WIDTH);
	return (buff->read);
}

char*			treat_flag_plus(t_buff *buff, char *input)
{
	if (ft_strchr("aAeEfFgGidD", SPECIF))
	{
		if (PLUS || *input == '-')
		{
			buff_append(buff, *input == '-' ? "-" : "+", 1);
			if (*input == '-')
				input++;
		}
	}
	return (input);
}

void			treat_htag(t_buff *buff, char *input)
{
	if (*input != '0' && HTAG)
	{
		if (ft_strchr("oO", SPECIF))
			buff_append(buff, "0", 1);
		else if (ft_strchr("xXp", SPECIF))
			buff_append(buff, SPECIF == 'X' ? "0X" : "0x", 2);
	}
}
