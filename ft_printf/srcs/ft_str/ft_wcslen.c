/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcslen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 18:31:39 by bopopovi          #+#    #+#             */
/*   Updated: 2018/07/26 16:29:15 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_wcslen(wchar_t *wcs)
{
	size_t	i;
	size_t	bytes;

	i = 0;
	bytes = 0;
	if (wcs)
	{
		while (wcs[i] != L'\0')
		{
			if ((wcs[i] > 255 && MB_CUR_MAX != 4) || wcs[i] < 0x0
				|| (wcs[i] >= 0xd800 && wcs[i] <= 0xdfff) || wcs[i] > 0x10ffff)
				return (-1);
			if (wcs[i] > 65536)
				bytes += 4;
			else if (wcs[i] > 2048)
				bytes += 3;
			else if (wcs[i] > 128)
				bytes += 2;
			else
				bytes++;
			i++;
		}
	}
	return (bytes);
}
