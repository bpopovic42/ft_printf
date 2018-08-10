/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse_args.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 18:44:17 by bopopovi          #+#    #+#             */
/*   Updated: 2018/07/31 17:45:46 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

	if (ft_strchr(FLAGS, '0') && (PRECISION < 0 || ft_strchr("sScC", SPECIF)))
		width = "0";
	else
		width = " ";
	if (INDEX > 0)
		dump_fmt(ptf);
	if (ft_strlen((char*)prefix) && *width == '0')
		buff_append(ptf, (char*)prefix, ft_strlen((char*)prefix));
	if (!ft_strchr(FLAGS, '-') && WIDTH > 0)
		buff_seqncat(ptf, width, WIDTH);
	if (ft_strlen((char*)prefix) && *width == ' ')
		buff_append(ptf, (char*)prefix, ft_strlen((char*)prefix));
	if (ft_strchr("DIOUXP", ft_toupper(SPECIF)) && PRECISION > 0)
		buff_seqncat(ptf, "0", PRECISION);
	if (SPECIF == 'S')
	{
		if ((print_wcs(ptf, input, size)) < 0)
			return (-1);
	}
	else
		buff_append(ptf, (char*)input, size);
	if (ft_toupper(SPECIF) == 'F' && PRECISION > 0)
		buff_seqncat(ptf, "0", PRECISION);
	if (ft_strchr(FLAGS, '-') && WIDTH > 0)
		buff_seqncat(ptf, " ", WIDTH);
	return (1);
}

void			dump_fmt(t_ptf *ptf)
{
	buff_append(ptf, (char*)FMT, INDEX);
	FMT += INDEX;
	INDEX = 0;
}
