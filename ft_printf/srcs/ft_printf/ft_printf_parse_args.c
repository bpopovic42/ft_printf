/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse_args.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 18:44:17 by bopopovi          #+#    #+#             */
/*   Updated: 2018/07/25 17:43:46 by bopopovi         ###   ########.fr       */
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
	else if (buff->flags.l == 'l' || SPECIF == 'D')
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
	{
		value = va_arg(ap, unsigned long);
	}
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

int			get_width_and_precision(t_buff *buff, char type, int size)
{
	int precision;

	precision = PRECISION > size ? PRECISION - size : 0;
	if (type == 's' || type == 'f')
	{
		if (WIDTH > size)
		{
			WIDTH -= size;
		}
		else
			WIDTH = 0;
	}
	else
	{
		if (WIDTH > size + (precision > 0 ? precision : 0))
			WIDTH -= size + (precision > 0 ? precision : 0);
		else
			WIDTH = 0;
	}
	if (WIDTH > 0 && SPACE)
		WIDTH--;
	return (1);
}

int			treat_arg_type_str(t_buff *buff, char type, long long value)
{
	int		size;

	size = 0;
	value = !value ? (unsigned long)"(null)" : value;
	size = type == 's' ? ft_strlen((char*)value) : ft_wcslen((wchar_t*)value);
	if (PRECISION >= 0)
		size = PRECISION;
	else if (type == 'S')
		size *= sizeof(wchar_t);
	if (type == 's')
	{
		get_width_and_precision(buff, 's', size);
		size = print_arg(buff, (char*)value, size);
	}
	else
		size = treat_arg_type_wcstr(buff, (wchar_t*)value, size);
	return (size);
}

int			treat_arg_type_wcstr(t_buff *buff, wchar_t *wcstr, size_t size)
{
	unsigned char	ptr[size * sizeof(wchar_t)];
	int				bytes;

	ft_bzero(ptr, size * sizeof(wchar_t) + 1);
	bytes = ft_wcstombs(ptr, wcstr, size);
	if (bytes < 0)
		return (-1);
	get_width_and_precision(buff, 's', bytes);
	return (print_arg(buff, (char*)ptr, bytes));
}

int			treat_arg_type_int(t_buff *buff, char type, long long value)
{
	unsigned char	ptr[19];
	int		size;

	size = 1;
	ft_bzero(ptr, 19);
	ZERO = PRECISION > 0 && ZERO ? 0 : ZERO;
	if (type == 'c')
		ptr[0] = value;
	else if (type == 'C')
	{
		size = !value ? buff_append(buff, "\0", 1) : ft_wctomb(ptr, value);
		if (size < 0)
			return (size);
	}
	else
		size = ft_printf_itoa((char*)ptr, value);
	if (PRECISION == 0 && ft_strchr("cC", SPECIF))
		ptr[0] = '\0';
	else
		get_width_and_precision(buff, 'd', size);
	return (print_arg(buff, (char*)ptr, size));
}

int			treat_arg_type_uint(t_buff *buff, char type, long long value)
{
	char	ptr[19];
	int		size;

	(void)type;
	size = 1;
	ft_bzero(ptr, 19);
	ZERO = PRECISION > 0 && ZERO ? 0 : ZERO;
	size = ft_printf_uitoa(ptr, value);
	get_width_and_precision(buff, 'u', size);
	return (print_arg(buff, ptr, size));
}

int			treat_arg_type_base(t_buff *buff, char type, long long value)
{
	char	ptr[65];
	int		size;

	size = 0;
	ft_bzero(ptr, 65);
	if (ft_strchr("oO", type))
		size = ft_printf_itoa_base(ptr, OCTAL, value);
	else
		size = ft_printf_itoa_base(ptr, type == 'X' ? HEXA_UP : HEXA, value);
	WIDTH -= HTAG && value ? (ft_strchr("oO", SPECIF) ? 1 : 2) : 0;
	get_width_and_precision(buff, 'b', !value && !PRECISION ? 0 : size);
	return (print_arg(buff, ptr, size));
}

int			treat_arg_type_dbl(t_buff *buff, char type, long long value)
{
	char	tmp[MAX_INT_LEN + 1 + (PRECISION >= 0 ? PRECISION : 6)]; // + precision
	int		size;

	ft_bzero(tmp, MAX_INT_LEN + 1 + (PRECISION >= 0 ? PRECISION : 6));
	size = 0;
	if (ft_strchr("fF", type))
		ft_ftoa(value, (PRECISION >= 0 ? PRECISION : 6), tmp);
	size = ft_strlen(tmp);
	get_width_and_precision(buff, 'f', size);
	return (print_arg(buff, tmp, size));
}

int			print_arg(t_buff *buff, char *input, int size)
{
	(void)size;
	if (ft_strchr("sS", SPECIF))
	{
		if (PRECISION >= 0)
		{
			if (!*input && WIDTH)
			{
				WIDTH += PRECISION;
				PRECISION = -1;
			}
			else
				input[PRECISION] = '\0';
		}
	}
	if (WIDTH > 0 && ZERO && HTAG)
		treat_htag(buff, input, size);
	if (!MINUS && WIDTH > 0 && ZERO)
	{
		input = treat_flag_plus(buff, input);
		buff_append(buff, " ", SPACE ? 1 : 0);
		buff_seqncat(buff, "0", WIDTH);
	}
	else if (!MINUS && WIDTH > 0 && !ZERO)
	{
		buff_seqncat(buff, " ", WIDTH - (PLUS && *input != '-' ? 1 : 0));
		input = treat_flag_plus(buff, input);
		buff_append(buff, " ", SPACE ? 1 : 0);
	}
	else
	{
		input = treat_flag_plus(buff, input);
		buff_append(buff, " ", SPACE ? 1 : 0);
	}
	if (!ZERO || (WIDTH <= 0 && HTAG))
		treat_htag(buff, input, size);
	if ((PRECISION - size) > 0 && !ft_strchr("sS", SPECIF))
		buff_seqncat(buff, "0", PRECISION - size);
	if (!(!PRECISION && *input == '0' && ft_strchr("aAdDeEfFgGiuUxX", SPECIF)))
		buff_append(buff, input, SPECIF == 'c' ? size : ft_strlen(input));
	if (MINUS && WIDTH >= 0)
		buff_seqncat(buff, ZERO ? "0" : " ", WIDTH);
	write(1, buff->buff, buff->pos);
	buff->read += buff->pos;
	buff->pos = 0;
	ft_bzero(buff->buff, BUFF_SIZE + 1);
	return (buff->read);
}

char*			treat_flag_plus(t_buff *buff, char *input)
{
	if (ft_strchr("aAeEfFgGidD", SPECIF))
	{
		if (PLUS || *input == '-')
		{
			SPACE = 0;
			buff_append(buff, *input == '-' ? "-" : "+", 1);
			if (*input == '-')
			{
				input++;
				if (PRECISION > 0)
					PRECISION++;
			}
			else if (PLUS)
				WIDTH--;
		}
	}
	return (input);
}

void			treat_htag(t_buff *buff, char *input, int arg_size)
{
	if (*input && *input != '0' && HTAG)
	{
		if (ft_strchr("oO", SPECIF))
		{
			if (PRECISION <= arg_size)
				PRECISION = arg_size + 1;
		}
		else if (ft_strchr("xXp", SPECIF))
			buff_append(buff, SPECIF == 'X' ? "0X" : "0x", 2);
	}
}
