/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcstombs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:48:37 by bopopovi          #+#    #+#             */
/*   Updated: 2018/06/13 15:49:03 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_wcstombs(char *s, wchar_t *wcs, size_t n)
{
	char	bytes[MB_LEN_MAX];
	size_t	total_b;
	int		mb_len;

	total_b = 0;
	while (*wcs && total_b < n)
	{
		ft_bzero(bytes, MB_LEN_MAX);
		mb_len = ft_wctomb(bytes, *wcs);
		if (mb_len < 0)
			return (-1);
		total_b += mb_len;
		if (n > 0)
			ft_strncat(s, bytes, mb_len);
		wcs++;
	}
	return (total_b);
}
