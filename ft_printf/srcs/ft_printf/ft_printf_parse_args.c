/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse_args.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 18:44:17 by bopopovi          #+#    #+#             */
/*   Updated: 2018/07/26 22:44:30 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long		get_varg(t_buff *buff, va_list ap)
{
	long long value;

	value = 0;
	if (ft_strchr("fFgGeE", SPECIF))
		value = va_arg(ap, double);
	else if (ft_strchr("sSuUxXoOp", SPECIF))
		value = get_varg_uint(buff, ap);
	else if (ft_strchr("dDicC", SPECIF))
		value = get_varg_int(buff, ap);
	return (value);
}

long long		get_varg_int(t_buff *buff, va_list ap)
{
	long long value;

	value = 0;
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

long long		get_varg_uint(t_buff *buff, va_list ap)
{
	long long value;

	value = 0;
	if (buff->flags.h == 'h' && SPECIF != 'U')
		value = (unsigned short)va_arg(ap, unsigned);
	else if (buff->flags.h == 'H')
		value = (unsigned char)va_arg(ap, unsigned);
	else if (buff->flags.l == 'l' || ft_strchr("sSUp", SPECIF))
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
	if (WIDTH > 0 && !ZERO)
		buff->spcs = WIDTH;
	else if (WIDTH > 0 && ZERO)
		buff->zero += WIDTH;
	return (1);
}

int			treat_arg_type_str(t_buff *buff, long long value)
{
	int		size;

	size = 0;
	value = !value ? (unsigned long)"(null)" : value;
	if (SPECIF == 's')
	{
		size = ft_strlen((char*)value);
		if (PRECISION >= 0 && PRECISION < size)
			size = PRECISION;
	}
	else
	{
		if (PRECISION > 0)
			size = ft_wcsnlen((wchar_t*)value, PRECISION);
		else
			size = ft_wcslen((wchar_t*)value);
	}
	get_width_and_precision(buff, 's', size);
	return (print_arg(buff, (int*)value, size));
}

int			treat_arg_type_int(t_buff *buff, long long value)
{
	unsigned char	ptr[19];
	int		size;

	size = 1;
	ft_bzero(ptr, 19);
	ZERO = PRECISION > 0 && ZERO ? 0 : ZERO; // TO MOVE
	if (SPECIF == 'c')
	{
		if (!value)
			PRECISION = -1;
		ptr[0] = value;
	}
	else if (SPECIF == 'C')
	{
		size = !value ? buff_append(buff, "\0", 1) : ft_wctomb(ptr, value);
		if (size < 0)
			return (size);
	}
	else
		size = ft_printf_itoa((char*)ptr, value);
	if (*ptr == '-' && PRECISION > 0)
		WIDTH--;
	if (!value && !PRECISION && WIDTH > 0)
		WIDTH++;
	if (PRECISION == 0 && (SPECIF == 'c' || SPECIF == 'C'))
		ptr[0] = '\0';
	else
		get_width_and_precision(buff, 'd', size);
	return (print_arg(buff, (int*)ptr, size));
}

int			treat_arg_type_uint(t_buff *buff, long long value)
{
	char	ptr[19];
	int		size;

	size = 1;
	ft_bzero(ptr, 19);
	ZERO = PRECISION > 0 && ZERO ? 0 : ZERO;
	size = ft_printf_uitoa(ptr, value);
	get_width_and_precision(buff, 'u', size);
	return (print_arg(buff, (int*)ptr, size));
}

int			treat_arg_type_base(t_buff *buff, long long value)
{
	char	ptr[65];
	int		size;

	size = 0;
	ft_bzero(ptr, 65);
	if (ft_strchr("oO", SPECIF))
		size = ft_printf_itoa_base(ptr, OCTAL, value);
	else
		size = ft_printf_itoa_base(ptr, SPECIF == 'X' ? HEXA_UP : HEXA, value);
	if (SPECIF == 'p' || (HTAG && value))
		WIDTH -= (ft_strchr("oO", SPECIF) ? 1 : 2);
	get_width_and_precision(buff, 'b', !value && !PRECISION ? 0 : size);
	return (print_arg(buff, (int*)ptr, size));
}

int			treat_arg_type_dbl(t_buff *buff, long long value)
{
	char	tmp[MAX_INT_LEN + 1 + (PRECISION >= 0 ? PRECISION : 6)]; // + precision
	int		size;

	ft_bzero(tmp, MAX_INT_LEN + 1 + (PRECISION >= 0 ? PRECISION : 6));
	size = 0;
	if (ft_strchr("fF", SPECIF))
		ft_ftoa(value, (PRECISION >= 0 ? PRECISION : 6), tmp);
	size = ft_strlen(tmp);
	get_width_and_precision(buff, 'f', size);
	return (print_arg(buff, (int*)tmp, size));
}

int				print_arg(t_buff *buff, int *input, int size)
{
	if (INDEX > 0)
		dump_fmt(buff);
	if (buff->spcs > 0 && !MINUS)
		buff_seqncat(buff, " ", buff->spcs);
	//IF HTAG PLUS ETC...
	if (buff->zero > 0)
		buff_seqncat(buff, "0", buff->zero);
	if (SPECIF == 'S')
		print_wcs(buff, input, size);
	else
		buff_append(buff, (char*)input, size);
	if (buff->spcs > 0 && MINUS)
		buff_seqncat(buff, " ", buff->spcs);
	write(1, buff->buff, buff->pos);
	buff->read += buff->pos;
	buff->pos = 0;
	ft_bzero(buff->buff, BUFF_SIZE);
	return (1);
}

int				print_wcs(t_buff *buff, int *input, int size)
{
	unsigned char	bytes[4];
	int				total_b;
	int				len;
	int				i;

	total_b = 0;
	i = 0;
	len = 0;
	if (SPECIF == 'S')
	{
		while (input[i] != L'\0')
		{
			ft_bzero(bytes, 4);
			len = ft_wctomb(bytes, (wchar_t)input[i]);
			total_b += len;
			if (total_b <= size)
				buff_append(buff, (char*)bytes, len);
			else
				break;
			i++;
		}
	}
	return (1);
}

void			dump_fmt(t_buff *buff)
{
	write(1, FMT, buff->fmti);
	FMT += buff->fmti;
	buff->read += buff->fmti;
	buff->fmti = 0;
}

/*int			print_arg(t_buff *buff, int *input, int size)
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
			else if (PRECISION <= size)
				size = PRECISION;
		}
	}
	if (WIDTH > 0 && ZERO && HTAG)
		treat_htag(buff, input, size);
	if (!MINUS && WIDTH > 0 && ZERO)
	{
		input = treat_flag_plus(buff, input);
		buff_append(buff, " ", SPACE && ft_strchr("aAfFeEdDgGi", SPECIF) ? 1 : 0);
		buff_seqncat(buff, "0", WIDTH);
	}
	else if (!MINUS && WIDTH > 0 && !ZERO)
	{
		buff_seqncat(buff, " ", WIDTH - (PLUS && *input != '-' ? 1 : 0));
		input = treat_flag_plus(buff, input);
		buff_append(buff, " ", SPACE && ft_strchr("aAfFeEdDgGi", SPECIF) ? 1 : 0);
	}
	else
	{
		input = treat_flag_plus(buff, input);
		buff_append(buff, " ", SPACE && ft_strchr("aAfFeEdDgGi", SPECIF) ? 1 : 0);
	}
	if (!ZERO || (WIDTH <= 0 && HTAG) || SPECIF == 'p')
		treat_htag(buff, input, size);
	if ((PRECISION - size) > 0 && !ft_strchr("sS", SPECIF))
		buff_seqncat(buff, "0", PRECISION - size);
	if (!(!PRECISION && *input == '0' && ft_strchr("aAdDeEfFgGiuUxXoO", SPECIF)))
		buff_append(buff, input, SPECIF == 'c'  || SPECIF == 's' ? size : ft_strlen(input));
	if (MINUS && WIDTH >= 0)
		buff_seqncat(buff, ZERO ? "0" : " ", WIDTH);
	write(1, buff->buff, buff->pos);
	buff->read += buff->pos;
	buff->pos = 0;
	ft_bzero(buff->buff, BUFF_SIZE + 1);
	return (buff->read);
}*/

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
	if ((*input && (*input != '0' || ft_strchr("oO", SPECIF)) && HTAG) || SPECIF == 'p')
	{
		if (ft_strchr("oO", SPECIF))
		{
			if (PRECISION <= arg_size && *input != '0')
				PRECISION = arg_size + 1;
			else if (PRECISION <= arg_size)
				PRECISION = 1;
		}
		if (ft_strchr("xXp", SPECIF))
			buff_append(buff, SPECIF == 'X' ? "0X" : "0x", 2);
	}
}
