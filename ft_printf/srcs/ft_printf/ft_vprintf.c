/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 19:06:52 by bopopovi          #+#    #+#             */
/*   Updated: 2018/07/11 21:14:49 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_vprintf(const char * restrict format, va_list ap)
{
	char	*ptr;
	size_t	line_size;
	t_buff	buff;

	ptr = (char*)format;
	ft_bzero(buff.buff, BUFF_SIZE + 1);
	buff.pos = 0;
	buff.read = 0;
	line_size = parse_input(ptr, &buff, ap);
	if (buff.pos != 0)
		line_size += write(1, buff.buff, buff.pos);
	return (line_size);
}

int			parse_input(char *fmt, t_buff *buff, va_list ap)
{
	int		read;
	int		ret;

	read = 0;
	ret = 0;
	while (*fmt)
	{
		if (*fmt != '%')
		{
			buff_append(buff, fmt, 1);
			fmt++;
			read++;
		}
		else
		{
			if (!*(fmt + 1))
				fmt++;
			else
				ret += treat_arg(buff, &fmt, ap);
		}
	}
	return (buff->read);
}

int			treat_arg(t_buff *buff, char **input, va_list ap)
{
	int			i;
	int			size;
	int			(*fptr)(t_buff*, char, va_list);

	i = 1;
	size = 0;
	reset_flags(&buff->flags);
	if ((i = get_flags(buff, input, i)) < 0)
		return (i);
	if (!(fptr = treat_specifier_by_type(buff->flags.specifier)))
	{
		if (buff->flags.specifier == '%')
			size += print_arg(buff, &buff->flags.specifier, 1);
		else
			return (-1);
	}
	else
		size = fptr(buff, buff->flags.specifier, ap);
	*input += i + 1;
	return (size);
}

int		(*treat_specifier_by_type(char specifier))(t_buff*, char, va_list)
{
	if (ft_strchr("sS", specifier))
		return (treat_arg_type_str);
	else if (ft_strchr("dDicC", specifier))
		return (treat_arg_type_int);
	else if (ft_strchr("uU", specifier))
		return (treat_arg_type_uint);
	else if (ft_strchr("poOxX", specifier))
		return (treat_arg_type_base);
	else if (ft_strchr("fFeEgGaA", specifier))
		return (treat_arg_type_dbl);
	return (NULL);
}
