/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse_args.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 18:44:17 by bopopovi          #+#    #+#             */
/*   Updated: 2018/07/29 22:08:25 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*int			get_width_and_precision(t_ptf *ptf, char type, int size)
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
}*/

int				print_wcs(t_ptf *ptf, int *input, int size)
{
	unsigned char	bytes[4];
	int				total_b;
	int				len;
	int				i;

	total_b = 0;
	i = 0;
	len = 0;
	while (input[i] != L'\0')
	{
		ft_bzero(bytes, 4);
		len = ft_wctomb(bytes, (wchar_t)input[i]);
		total_b += len;
		if (total_b <= size)
		{
			buff_append(ptf, (char*)bytes, len);
			if (total_b == size)
				return (1);
		}
		else
			break;
		i++;
	}
	return (1);
}

int				print_arg(t_ptf *ptf, int *prefix, int *input, int size)
{
	char *width;

	width = ft_strchr(FLAGS, '0') && PRECISION < 0 ? "0" : " ";
	if (INDEX > 0)
		dump_fmt(ptf);
	if (ft_strlen((char*)prefix) && *width == '0')
		buff_append(ptf, (char*)prefix, ft_strlen((char*)prefix));
	if (!ft_strchr(FLAGS, '-') && WIDTH > 0)
		buff_seqncat(ptf, width, WIDTH);
	if (ft_strlen((char*)prefix) && *width == ' ')
		buff_append(ptf, (char*)prefix, ft_strlen((char*)prefix));
	if (ft_strchr("dDioOuUxX", SPECIF) && PRECISION > 0)
		buff_seqncat(ptf, "0", PRECISION);
	if (SPECIF == 'S')
	{
		if ((print_wcs(ptf, input, size)) < 0)
			return (-1);
	}
	else
		buff_append(ptf, (char*)input, size);
	if (ft_strchr(FLAGS, '-') && WIDTH > 0)
		buff_seqncat(ptf, " ", WIDTH);
	write(1, ptf->buff.buff, ptf->buff.pos);
	ptf->buff.read += ptf->buff.pos;
	ptf->buff.pos = 0;
	ft_bzero(ptf->buff.buff, BUFF_SIZE);
	return (1);
}

void			dump_fmt(t_ptf *ptf)
{
	write(1, FMT, INDEX);
	FMT += INDEX;
	ptf->buff.read += INDEX;
	INDEX = 0;
}
