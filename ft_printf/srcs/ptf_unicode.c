/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf_unicode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 14:50:37 by bopopovi          #+#    #+#             */
/*   Updated: 2018/06/12 18:39:26 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ptf_wcs(wchar_t *s, t_buff *buff)
{
	while (*s)
	{
		ft_wctomb(buff->buff, *s);
		s++;
	}
}

int		ft_wctomb(char *s, wchar_t wc)
{
	int	shift;
	int i;

	ft_bzero(s, MB_LEN_MAX);
	shift = 24;
	i = 0;
	s[0] = wc <= 127 ? wc : 0;
	wc = wc <= 127 ? 0 : wc;
	s[0] += wc > 127 ? 64 : 0;
	s[0] += wc > 4096 ? 32 : 0;
	s[0] += wc > 262144 ? 16 : 0;
	while (shift > 0)
	{
		shift -= 6;
		if ((wc >> shift) != 0 || i != 0)
		{
			s[i] += (wc >> shift) + 128;
			wc ^= (wc >> shift) << shift;
			i++;
		}
	}
	s[MB_LEN_MAX - 1] = '\0';
	return (i);
}
