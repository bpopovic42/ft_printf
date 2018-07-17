/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse_args.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 18:44:17 by bopopovi          #+#    #+#             */
/*   Updated: 2018/07/17 19:51:15 by bopopovi         ###   ########.fr       */
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
		size = print_arg(buff, (char*)value, value ? ft_strlen((char*)value) : 0);
	}
	else if (type == 'S' || (type == 's' && buff->flags.l == 'l'))
	{
		if (!value)
			value = (unsigned long)&L"(null)";
		size = treat_arg_type_wcstr(buff, (wchar_t*)value, ft_wcslen((wchar_t*)value));
	}
	return (size);
}

int			treat_arg_type_wcstr(t_buff *buff, wchar_t *wcstr, size_t size)
{
	unsigned char	ptr[size * sizeof(wchar_t) + 1];
	size_t			bytes;

	ft_bzero(ptr, size * sizeof(wchar_t) + 1);
	bytes = ft_wcstombs(ptr, wcstr, size * sizeof(wchar_t));
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
	}
	return (print_arg(buff, tmp, size));
}

int			print_arg(t_buff *buff, char *input, int size)
{
	int		added_size;
	int		i;

	added_size = 0;
	i = 0;
	if (ft_strchr("aAdeEfFgGi", SPECIF) && (PLUS || (*input == '-' && !MINUS)))
	{
		if (*input == '-')
		{
			input++;
			size--;
			PLUS = '-';
		}
		added_size++;
		WIDTH--;
	}

	if (size > 0 && PRECISION >= 0 && SPECIF == 's')
	{
		input[PRECISION] = '\0';
		size = PRECISION;
	}

	if (!MINUS)
	{
		if (SPECIF == 'c' && !*input)
		{
			if (WIDTH > 0)
				size = 1;
			else
				PRECISION = 0;
		}
		added_size += treat_precision(buff, input, size);
	}

	if (HTAG && ft_strchr("xXoOp", SPECIF))
	{
		if ((size > 0 && *input != '0' && ft_strchr("xX", SPECIF) && !ZERO) || SPECIF == 'p')
			SPECIF == 'X' ? buff_append(buff, "0X", 2) : buff_append(buff, "0x", 2);
		else if (ft_strchr("oO", SPECIF))
			added_size += buff_append(buff, "0", 1);
	}

	size = (!PRECISION && *input == '0') ? 0 : size;

	if (ft_strchr("aAdeEfFgGi", SPECIF) && (PLUS || SPACE))
	{
		if (PLUS && buff->buff[POS - 1] != '0')
			buff_append(buff, &PLUS, 1);
		else if (SPACE && buff->buff[POS - 1] != ' ')
			added_size += buff_append(buff, " ", 1);
	}

	if (PRECISION > size && ft_strchr("dioOuUxX", SPECIF))
	{
		added_size += buff_seqncat(buff, "0", PRECISION - size);
		WIDTH -= PRECISION - size;
		PRECISION -= PRECISION - size;
	}

	if ((input && *input) || SPECIF == 'c')
		size = buff_append(buff, input, size < PRECISION || PRECISION < 1  || !ft_strchr("sS", SPECIF) ? size : PRECISION);

	if (HTAG && ft_strchr("aAeEfFgG", SPECIF) && !ft_strchr(input, '.'))
		buff_append(buff, ".", 1);

	if (MINUS)
		added_size += treat_precision(buff, input, size);

	return (added_size + size + ((ft_strchr("xX", SPECIF) && HTAG && input[0] != '0') || SPECIF == 'p' ? 2 : 0));
}
