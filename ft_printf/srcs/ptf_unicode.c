/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf_unicode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 14:50:37 by bopopovi          #+#    #+#             */
/*   Updated: 2018/06/11 18:37:24 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ptf_wcs(wchar_t *s, t_buff *buff)
{
	while (*s)
	{
		ptf_wc(*s, buff);
		s++;
	}
}

int		ptf_wc(wchar_t c, t_buff *buff)
{
	unsigned char			bytes[5];
	int	shift;
	int i;

	ft_bzero(bytes, 5);
	shift = 24;
	i = 0;
	bytes[0] = c <= 127 ? c : 0;
	c = c <= 127 ? 0 : c;
	bytes[0] += c > 127 ? 64 : 0;
	bytes[0] += c > 4096 ? 32 : 0;
	bytes[0] += c > 262144 ? 16 : 0;
	while (shift > 0)
	{
		shift -= 6;
		if ((c >> shift) != 0 || i != 0)
		{
			bytes[i] += (c >> shift) + 128;
			c ^= (c >> shift) << shift;
			i++;
		}
	}
	fill_buffer(buff, bytes, i);
	//write(1, &bytes, i == 0 ? 1 : i);
	//write(1, &bytes, 5);
	return (i);
}
