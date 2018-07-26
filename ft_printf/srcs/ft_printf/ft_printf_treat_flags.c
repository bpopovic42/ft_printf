/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_treat_flags.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 19:03:18 by bopopovi          #+#    #+#             */
/*   Updated: 2018/07/26 21:25:45 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			get_flags(t_buff *buff, int i)
{
	while (FMT[i] && !ft_printf_is_fspecif(FMT[i]))
	{
		if (!ft_printf_is_flag(FMT[i]))
			return (i - 1);
		if (FMT[i] == '.')
			i += ft_printf_atoi(FMT + i + 1, &(buff->flags.precision));
		else if (ft_strchr("123456789", FMT[i]) && !buff->flags.width)
			i += ft_printf_atoi(FMT + i, &(buff->flags.width)) - 1;
		save_flags(buff, FMT[i], i);
		i++;
	}
	SPECIF = FMT[i];
	if (buff->flags.l == 'l')
	{
		if (SPECIF == 'c')
			SPECIF = 'C';
		else if (SPECIF == 's')
			SPECIF = 'S';
		else if (SPECIF == 'd')
			SPECIF = 'D';
		else if (SPECIF == 'u')
			SPECIF ='U';
		else if (!(ft_strchr("oOxX", SPECIF)))
		{
			buff->flags.l = 0;
		}
	}
	if (PRECISION >= 0 && ft_strchr("dDioOuUxX", SPECIF))
		ZERO = 0;
	return (i);
}

void		save_flags(t_buff *buff, int c, int i)
{
		buff->flags.htag = c == '#' ? true : buff->flags.htag;
		buff->flags.zero = c == '0' && ((i == 1 && !buff->flags.htag) || (i == 2 && (buff->flags.htag || SPACE))) ? true : buff->flags.zero;
		buff->flags.minus = c == '-' ? true : buff->flags.minus;
		buff->flags.space = c == ' ' ? true : buff->flags.space;
		buff->flags.plus = c == '+' ? '+' : buff->flags.plus;
		buff->flags.apos = c == '\'' ? true : buff->flags.apos;
		buff->flags.j = c == 'j' ? true : buff->flags.j;
		buff->flags.z = c == 'z' ? true : buff->flags.z;
		if (c == 'h')
		{
			if (buff->flags.h == 'h')
				buff->flags.h = 'H';
			else
				buff->flags.h = 'h';
		}
		if (c == 'l')
		{
			if (buff->flags.l == 'l')
				buff->flags.l = 'L';
			else
				buff->flags.l = 'l';
		}
}

void		reset_flags(t_flags *flags)
{
	flags->htag = false;
	flags->zero = false;
	flags->minus = false;
	flags->space = false;
	flags->plus = 0;
	flags->apos = false;
	flags->j = false;
	flags->z = false;
	flags->l = 0;
	flags->h = 0;
	flags->width = 0;
	flags->precision = -1;
	flags->htag = 0;
}

int			treat_precision(t_buff *buff, char *input, int arg_size)
{
	int		added_len;

	added_len = 0;
	if (!buff->flags.precision && ft_strchr("dioOuUxX", buff->flags.specifier) && input[0] == '0' && buff->flags.width > 0)
		added_len += buff_append(buff, " ", 1);

	if (buff->flags.zero && buff->flags.htag && ft_strchr("pxX", buff->flags.specifier))
		buff->flags.specifier == 'X' ? buff_append(buff, "0X", 2) : buff_append(buff, "0x", 2);

	if (buff->flags.precision < buff->flags.width && arg_size < buff->flags.width)
	{
		if (ft_strchr("aAdeEfFgGi", buff->flags.specifier) && buff->flags.plus && (((buff->flags.width > arg_size || buff->flags.width > buff->flags.precision) && buff->flags.zero) && !buff->flags.minus))
			buff_append(buff, &buff->flags.plus, 1);

		buff->flags.width -= (buff->flags.precision > arg_size && buff->flags.precision > 0  && arg_size > 0 ? buff->flags.precision : arg_size);
		while (buff->flags.width)
		{
			added_len += buff_append(buff, buff->flags.zero ? "0" : " ", 1);
			buff->flags.width--;
		}
	}

	return (added_len);
}
