/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf_unicode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 14:50:37 by bopopovi          #+#    #+#             */
/*   Updated: 2018/06/12 22:24:50 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_app(char *s1, char *s2, size_t n);

int		ft_wcstombs(char *s, wchar_t *wcs, size_t n)
{
	char	bytes[MB_LEN_MAX];
	size_t	total_b;
	size_t	mb_len;

	total_b = 0;
	while (*wcs && total_b < n)
	{
		ft_bzero(bytes, MB_LEN_MAX);
		mb_len = ft_wctomb(bytes, *wcs);
		if (mb_len <= 0)
			return (-1);
		total_b += mb_len;
		if (n > 0)
			ft_app(s, bytes, mb_len);
		wcs++;
	}
	return (total_b);
}

void	ft_app(char *s1, char *s2, size_t n)
{
	int i = 0;

	while (s1[i])
		i++;
	while (*s2 && n > 0)
	{
		s1[i] = *s2;
		n--;
		i++;
		s2++;
	}
}

#include <stdio.h>

int		ft_wctomb(char *s, wchar_t wc)
{
	int	shift;
	int i;

	shift = 18;
	i = 0;
	if (wc >= 4194304 || wc <= 0)
		return (-1);
	while ((wc >> shift) == 0 && (wc >> (shift - 1)) == 0)
	{
		shift -= 6;
	}
	s[0] = wc <= 127 ? wc : 0;
	shift = wc <= 127 ? -1 : shift;
	wc = wc <= 127 ? 0 : wc;
	s[0] += wc > 127 ? 64 : 0;
	s[0] += wc > 2048 ? 32 : 0;
	s[0] += wc > 65536 ? 16 : 0;
	while (shift >= 0)
	{
			s[i] += (wc >> shift) + 128;
			wc ^= (wc >> shift) << shift;
			i++;
		shift -= 6;
	}
	return (i);
}
