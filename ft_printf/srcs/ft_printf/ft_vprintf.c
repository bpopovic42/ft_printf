/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 19:06:52 by bopopovi          #+#    #+#             */
/*   Updated: 2018/07/26 21:27:48 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_vprintf(const char * restrict format, va_list ap)
{
	char	*ptr;
	int		line_size;
	t_buff	buff;

	ptr = (char*)format;
	ft_bzero(buff.buff, BUFF_SIZE + 1);
	buff.pos = 0;
	buff.read = 0;
	buff.fmt = format;
	buff.fmti = 0;
	buff.spcs = 0;
	buff.zero = 0;
	line_size = parse_input(ptr, &buff, ap);
	if (buff.pos != 0 && line_size >= 0)
		line_size += write(1, buff.buff, buff.pos);
	return (line_size);
}

int			parse_input(char *fmt, t_buff *buff, va_list ap)
{
	while (*FMT && FMT[INDEX])
	{
		if (FMT[INDEX] == '%')
		{
			if (!FMT[1])
				FMT++;
			else
			{
				if ((treat_arg(buff, &fmt, ap)) < 0)
					return (-1);
			}
		}
		else
			INDEX++;
	}
	if (!FMT[INDEX] && *FMT)
		buff->read += write(1, FMT, INDEX);
	return (buff->read);
}

int			treat_arg(t_buff *buff, char **input, va_list ap)
{
	int			i;
	int			size;
	int			(*fptr)(t_buff*, char, long long);

	(void)input;
	i = 1;
	size = 0;
	reset_flags(&buff->flags);
	i = get_flags(buff, i + INDEX) - INDEX;
	if ((fptr = treat_specifier_by_type(buff->flags.specifier)))
		size = fptr(buff, buff->flags.specifier, get_varg(buff, SPECIF, ap));
	else if (buff->flags.specifier == '%')
	{
		WIDTH--;
		PRECISION = -1;
		size = print_arg(buff, (int*)&buff->flags.specifier, 1);
	}
	FMT += i + 1;
	INDEX = 0;
	return (size);
}

int		(*treat_specifier_by_type(char specifier))(t_buff*, char, long long)
{
	if (ft_strchr("sS", specifier))
		return (treat_arg_type_str);
	if (ft_strchr("dDicC", specifier))
		return (treat_arg_type_int);
	else if (ft_strchr("uU", specifier))
		return (treat_arg_type_uint);
	else if (ft_strchr("poOxX", specifier))
		return (treat_arg_type_base);
	else if (ft_strchr("fFeEgGaA", specifier))
		return (treat_arg_type_dbl);
	return (NULL);
}
