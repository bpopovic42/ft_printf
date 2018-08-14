/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print_arg.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 18:44:17 by bopopovi          #+#    #+#             */
/*   Updated: 2018/08/14 19:46:33 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_printf_print_wcs(t_ptf *ptf, int *input, int size)
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
			ft_printf_buff_cat(ptf, (char*)bytes, len);
			if (total_b == size)
				return (1);
		}
		else
			break;
		i++;
	}
	return (1);
}

int				ft_printf_print_arg(t_ptf *ptf, int *prfx, int *input, int size)
{
	char *width;

	if (ft_strchr(ptf->flags, '0') && (ptf->precision < 0 || ft_strchr("sScC", ptf->spec)))
		width = "0";
	else
		width = " ";
	if (ptf->fmt.i > 0)
		ft_printf_dump_fmt(ptf);
	if (ft_strlen((char*)prfx) && *width == '0')
		ft_printf_buff_cat(ptf, (char*)prfx, ft_strlen((char*)prfx));
	if (!ft_strchr(ptf->flags, '-') && ptf->width > 0)
		ft_printf_buff_catn(ptf, width, ptf->width);
	if (ft_strlen((char*)prfx) && *width == ' ')
		ft_printf_buff_cat(ptf, (char*)prfx, ft_strlen((char*)prfx));
	if (ft_strchr("BDIOUXP", ft_toupper(ptf->spec)) && ptf->precision > 0)
		ft_printf_buff_catn(ptf, "0", ptf->precision);
	if (ptf->spec == 'S')
	{
		if ((ft_printf_print_wcs(ptf, input, size)) < 0)
			return (-1);
	}
	else
		ft_printf_buff_cat(ptf, (char*)input, size);
	if (ft_toupper(ptf->spec) == 'F' && ptf->precision > 0)
		ft_printf_buff_catn(ptf, "0", ptf->precision);
	if (ft_strchr(ptf->flags, '-') && (int)ptf->width > 0)
		ft_printf_buff_catn(ptf, " ", ptf->width);
	return (1);
}
