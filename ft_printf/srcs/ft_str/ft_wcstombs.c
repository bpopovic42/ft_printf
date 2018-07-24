/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcstombs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:48:37 by bopopovi          #+#    #+#             */
/*   Updated: 2018/07/24 23:15:18 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <wchar.h>
#include <limits.h>

int		ft_wcstombs(unsigned char *s, wchar_t *wcs, size_t n)
{
	unsigned char	bytes[MB_LEN_MAX];
	size_t			total_b;
	int				mb_len;

	total_b = 0;
	while (*wcs && total_b < n)
	{
		ft_bzero(bytes, MB_LEN_MAX);
		mb_len = ft_wctomb(bytes, *wcs);
		if (mb_len < 0)
			return (-1);
		total_b += mb_len;
		if (total_b < n)
			ft_strncat((char*)s, (char*)bytes, mb_len);
		wcs++;
	}
	return (total_b);
}
