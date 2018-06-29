/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_treat_flags.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 19:03:18 by bopopovi          #+#    #+#             */
/*   Updated: 2018/06/29 19:19:04 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			get_flags(t_buff *buff, char **input, int i)
{
	while ((*input)[i] && !ft_printf_is_fspecif((*input)[i]))
	{
		if ((*input)[i] == '.')
		{
			buff->flags.precision = ft_atoi((*input) + i + 1);
			while (ft_isdigit((*input)[i + 1]) && (*input)[i + 1])
				i++;
		}
		else if (ft_strchr("123456789", (*input)[i]) && !buff->flags.width)
		{
			buff->flags.width = ft_atoi((*input) + i);
			while (ft_isdigit((*input)[i + 1]) && (*input)[i + 1])
				i++;
		}
		buff->flags.htag = (*input)[i] == '#' ? true : false;
		buff->flags.zero = (*input)[i] == '0' ? true : false;
		buff->flags.minus = (*input)[i] == '-' ? true : false;
		buff->flags.space = (*input)[i] == ' ' ? true : false;
		buff->flags.plus = (*input)[i] == '+' ? true : false;
		buff->flags.apos = (*input)[i] == '\'' ? true : false;
		i++;
	}
	if (ft_strchr("diouixX", buff->flags.specifier) && buff->flags.zero && buff->flags.precision)
		buff->flags.zero = 0;
	if (buff->flags.minus && buff->flags.zero)
		buff->flags.zero = 0;
	if (buff->flags.space && buff->flags.plus)
		buff->flags.space = 0;
	buff->flags.specifier = (*input)[i];
	return (i);
}

void		reset_flags(t_flags *flags)
{
	flags->htag = false;
	flags->zero = false;
	flags->minus = false;
	flags->space = false;
	flags->plus = false;
	flags->apos = false;
	flags->width = 0;
	flags->precision = 0;
	flags->htag = 0;
}

int			treat_precision(t_buff *buff, int arg_size)
{
	int		added_len;

	added_len = 0;
	if (buff->flags.precision < buff->flags.width && arg_size < buff->flags.width)
	{
		buff->flags.width -= (buff->flags.precision > arg_size ? buff->flags.precision : arg_size);
		while (buff->flags.width)
		{
			added_len += buff_append(buff, buff->flags.zero ? "0" : " ", 1);
			buff->flags.width--;
		}
	}
	if (arg_size < buff->flags.precision)
	{
		buff->flags.precision -= arg_size;
		while (buff->flags.precision)
		{
			added_len += buff_append(buff, "0", 1);
			buff->flags.precision--;
		}
	}
	return (added_len);
}
