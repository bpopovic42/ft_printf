/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print_arg.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 18:44:17 by bopopovi          #+#    #+#             */
/*   Updated: 2018/09/04 16:39:02 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Used to print the 'S' argument in regard to wchar_t handling rules
** Function
*/

void			ft_printf_print_wcs(t_ptf *ptf, wchar_t *input, int n)
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
		len = ft_wctomb(bytes, input[i]);
		total_b += len;
		if (total_b <= n)
		{
			ft_printf_buff_cat(ptf, (char*)bytes, len);
			if (total_b == n)
				break ;
		}
		else
			break ;
		i++;
	}
}

/*
** Dump parsed part of the format string
** Decides wether width should be space or zero
** Then proceeds to print formated arg and its computed prefix and or suffix
** If the specifier is 'S' or 'r' arg are send to their dedicated functions
** Functions returns 1 in case of success and -1 if 'S' returns an error
*/

int				ft_printf_print_arg(t_ptf *ptf, char *prfx, char *input, int n)
{
	char *width;

	ft_printf_dump_fmt(ptf);
	width = " ";
	if (ft_strchr(ptf->flags, '0'))
		width = ptf->precision < 0 || ft_strchr("rsScC", ptf->spec) ? "0" : " ";
	if (ft_strlen(prfx) && *width == '0')
		ft_printf_buff_cat(ptf, prfx, ft_strlen(prfx));
	if (!ft_strchr(ptf->flags, '-') && ptf->width > 0)
		ft_printf_buff_catn(ptf, width, ptf->width);
	if (ft_strlen(prfx) && *width == ' ')
		ft_printf_buff_cat(ptf, prfx, ft_strlen(prfx));
	if (ft_strchr("BDIOUXP", ft_toupper(ptf->spec)) && ptf->precision > 0)
		ft_printf_buff_catn(ptf, "0", ptf->precision);
	if (ptf->spec == 'S')
		ft_printf_print_wcs(ptf, (wchar_t*)input, n);
	else if (ptf->spec == 'r')
		ft_printf_buff_cat_npr(ptf, input, n);
	else if (ptf->spec != 'S')
		ft_printf_buff_cat(ptf, input, n);
	if (ft_strchr("AEF", ft_toupper(ptf->spec)) && ptf->precision > 0)
		ft_printf_buff_catn(ptf, "0", ptf->precision);
	if (ft_strchr(ptf->flags, '-') && (int)ptf->width > 0)
		ft_printf_buff_catn(ptf, " ", ptf->width);
	return (1);
}
