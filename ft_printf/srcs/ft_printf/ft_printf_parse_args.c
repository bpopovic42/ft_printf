/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse_args.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 18:44:17 by bopopovi          #+#    #+#             */
/*   Updated: 2018/07/17 15:04:34 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			treat_arg_type_str(t_buff *buff, char type, va_list ap)
{
	char	*ptr;
	wchar_t	*wptr;
	int		size;

	size = 0;
	if (type == 's' && buff->flags.l != 'l')
	{
		ptr = va_arg(ap, char *);
		if (!ptr)
			ptr = "(null)";
		size = print_arg(buff, ptr, ptr ? ft_strlen(ptr) : 0);
	}
	else if (type == 'S' || (type == 's' && buff->flags.l == 'l'))
	{
		wptr = va_arg(ap, wchar_t *);
		if (!wptr)
			wptr = L"(null)";
		size = treat_arg_type_wcstr(buff, wptr, ft_wcslen(wptr));
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

int			treat_arg_type_int(t_buff *buff, char type, va_list ap)
{
	char	ptr[19];
	int		size;
	int64_t		tmp;
	short int	tmp2;
	signed char	tmp3;
	wchar_t		tmp4;

	size = 1;
	ft_bzero(ptr, 19);
	if (buff->flags.l == 'l' && type == 'c')
		type = 'C';
	if ((buff->flags.l == 'l' || type == 'D') && type != 'C')
		tmp = va_arg(ap, long);
	else if (buff->flags.l == 'L')
		tmp = va_arg(ap, long long);
	else if (buff->flags.j)
		tmp = va_arg(ap, intmax_t);
	else if (buff->flags.z)
		tmp = va_arg(ap, size_t);
	else if (buff->flags.h == 'h')
		tmp2 = va_arg(ap, int);
	else if (buff->flags.h == 'H')
		tmp3 = va_arg(ap, int);
	else if (type == 'C')
		tmp4 = va_arg(ap, wchar_t);
	else
		tmp = va_arg(ap, int);
	if (PRECISION > 0 && ZERO)
		ZERO = 0;
	if (buff->flags.h == 'h')
		size = ft_printf_itoa((char*)ptr, tmp2);
	else if (buff->flags.h == 'H')
		size = ft_printf_itoa((char*)ptr, tmp3);
	else if (type == 'd' || type == 'i' || type == 'D')
		size = ft_printf_itoa((char*)ptr, tmp);
	else if (type == 'c')
		ptr[0] = tmp;
	else if (type == 'C')
	{
		if (!tmp4)
			size = buff_append(buff, "\0", 1);
		else
			size = ft_wctomb((unsigned char*)ptr, tmp4);
	}
	return (print_arg(buff, ptr, size));
}

int			treat_arg_type_uint(t_buff *buff, char type, va_list ap)
{
	char	ptr[19];
	int		size;
	uint64_t		tmp;
	unsigned char	tmp2;
	unsigned short	tmp3;

	size = 1;
	ft_bzero(ptr, 19);
	if (buff->flags.l == 'l' || type == 'U')
		tmp = va_arg(ap, unsigned long);
	else if (buff->flags.l == 'L')
		tmp = va_arg(ap, unsigned long long);
	else if (buff->flags.h == 'h')
		tmp3 = va_arg(ap, unsigned int);
	else if (buff->flags.h == 'H')
		tmp2 = va_arg(ap, unsigned int);
	else if (buff->flags.j)
		tmp = va_arg(ap, uintmax_t);
	else if (buff->flags.z)
		tmp = va_arg(ap, size_t);
	else
		tmp = va_arg(ap, unsigned int);
	if (PRECISION > 0 && ZERO)
		ZERO = 0;
	if (buff->flags.h == 'h' && type != 'U')
		size = ft_printf_uitoa(ptr, tmp3);
	else if (buff->flags.h == 'H' && type != 'U')
		size = ft_printf_uitoa(ptr, tmp2);
	else if (type == 'u' || type == 'U')
		size = ft_printf_uitoa(ptr, tmp);
	return (print_arg(buff, ptr, size));
}

int			treat_arg_type_base(t_buff *buff, char type, va_list ap)
{
	char	ptr[65];
	int		size;
	uint64_t	tmp;

	size = 0;
	ft_bzero(ptr, 65);
	if (buff->flags.l == 'l' || SPECIF == 'p' || type == 'O')
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
		size = ft_printf_itoa_base(ptr, HEXA, tmp);
	else if (type == 'o' || type == 'O')
		size = ft_printf_itoa_base(ptr, OCTAL, tmp);
	else if (type == 'x' || type == 'X')
		size = ft_printf_itoa_base(ptr, type == 'X' ? HEXA_UP : HEXA, tmp);
	if (ft_strchr("pxX", SPECIF) && HTAG && WIDTH >= 2 && size && ptr[0] != '0')
		WIDTH -= 2;
	if (HTAG && ft_strchr("oO", SPECIF) && WIDTH > 0)
		WIDTH--;
	return (print_arg(buff, ptr, size));
}

int			treat_arg_type_dbl(t_buff *buff, char type, va_list ap)
{
	char	tmp[MAX_INT_LEN + 1 + (PRECISION >= 0 ? PRECISION : 6)]; // + precision
	int		size;

	ft_bzero(tmp, MAX_INT_LEN + 1 + (PRECISION >= 0 ? PRECISION : 6));
	size = 0;
	if (ft_strchr("fF", type))
	{
		ft_ftoa(va_arg(ap, double), (PRECISION >= 0 ? PRECISION : 6), tmp);
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
		if (SPECIF == 'c' && !*input && WIDTH > 0)
			size = 1;
		if (SPECIF == 'c' && !*input && WIDTH <= 0)
			PRECISION = 0;
		added_size += treat_precision(buff, input, size);
	}

	if ((HTAG && size >= 1 && input[0] != '0' && ft_strchr("xX", SPECIF) && !ZERO) || SPECIF == 'p')
		SPECIF == 'X' ? buff_append(buff, "0X", 2) : buff_append(buff, "0x", 2);

	if (HTAG && ft_strchr("oO", SPECIF))
		added_size += buff_append(buff, "0", 1);

	size = !PRECISION && input[0] == '0' ? 0 : size;

	if (ft_strchr("aAdeEfFgGi", SPECIF) && PLUS && ((POS > 0 && buff->buff[POS - 1] != '0') || POS == 0))
		buff_append(buff, &PLUS, 1);
	else if (ft_strchr("AadeEfFgGi", SPECIF) && SPACE && (POS == 0 || buff->buff[POS - 1] != ' '))
		added_size += buff_append(buff, " ", 1);

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
