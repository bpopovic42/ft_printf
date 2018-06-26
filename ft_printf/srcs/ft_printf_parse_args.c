/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse_args.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 18:44:17 by bopopovi          #+#    #+#             */
/*   Updated: 2018/06/26 19:38:44 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			treat_arg(t_buff *buff, char **input, va_list ap)
{
	int			i;
	int			size;

	i = 1;
	size = 0;
	if ((*input)[i] == '%')
		buff_append(buff, *input + i, 1);
	else
	{
		while (!ft_printf_is_fspecif((*input)[i]))
			i++;
	}
	if (ft_strchr("sS", (*input)[i]))
		size += treat_arg_type_str(buff, (*input)[i], ap);
	else if (ft_strchr("pdDioOuUxXcC", (*input)[i]))
		size += treat_arg_type_int(buff, (*input)[i], ap);
	else if (ft_strchr("fFeEgG", (*input)[i]))
		size += treat_arg_type_dbl(buff, (*input)[i], ap);
	*input += i + 1;
	return (size);
}

int			treat_arg_type_str(t_buff *buff, char type, va_list ap)
{
	char	*ptr;
	wchar_t	*wptr;
	int		size;

	size = 0;
	if (type == 's')
	{
		ptr = va_arg(ap, char *);
		size = buff_append(buff, ptr, ft_strlen(ptr));
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
	char	ptr[size * sizeof(wchar_t)];
	size_t	bytes;

	ft_bzero(ptr, size * sizeof(wchar_t) + 1);
	bytes = ft_wcstombs(ptr, wcstr, size * sizeof(wchar_t));
	buff_append(buff, ptr, bytes);
	return (bytes);
}

int			treat_arg_type_int(t_buff *buff, char type, va_list ap)
{
	char	ptr[19];
	int		size;

	size = 1;
	ft_bzero(ptr, 19);
	if (type == 'd' || type == 'i' || type == 'D')
		size = ft_printf_itoa(ptr, va_arg(ap, int64_t));
	else if (type == 'c')
		ptr[0] = va_arg(ap, int);
	buff_append(buff, ptr, size);
	return (size);
}

int			treat_arg_type_dbl(t_buff *buff, char type, va_list ap)
{
	char	tmp[MAX_INT_LEN + 1]; // + precision
	int		size;

	ft_bzero(tmp, MAX_INT_LEN + 1);
	size = 0;
	if (type == 'f')
	{
		ft_ftoa(va_arg(ap, double), 6, tmp);
		size = ft_strlen(tmp);
	}
	buff_append(buff, tmp, size);
	return (size);
}
