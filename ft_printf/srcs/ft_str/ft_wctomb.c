/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wctomb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:48:00 by bopopovi          #+#    #+#             */
/*   Updated: 2018/06/26 18:15:46 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_wctomb(char *s, wchar_t wc)
{
	int	shift;
	int i;

	shift = 18;
	i = 0;
	if (!s)
		return (0);
	else if ((wc > 255 && MB_CUR_MAX == 1) || wc < 0x0
		|| (wc >= 0xd800 && wc <= 0xdfff) || wc > 0x10ffff)
		return (-1);
	while ((wc >> shift) == 0 && (wc >> (shift - 1)) == 0)
		shift -= 6;
	s[0] = wc < 128 ? wc : 64;
	if (wc < 128)
		return (1);
	s[0] += wc > 2048 ? 32 : 0;
	s[0] += wc > 65536 ? 16 : 0;
	while (shift >= 0)
	{
		s[i++] += (wc >> shift) + 128;
		wc ^= (wc >> shift) << shift;
		shift -= 6;
	}
	return (i);
}
