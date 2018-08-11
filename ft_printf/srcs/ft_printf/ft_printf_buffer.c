/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_buffer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 18:48:52 by bopopovi          #+#    #+#             */
/*   Updated: 2018/08/11 02:20:09 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			buff_append(t_ptf *ptf, char *input, int size)
{
	int i;
	char *buff;

	i = 0;
	buff = ptf->buff.buff;
	while (size)
	{
		if (ptf->buff.pos == BUFF_SIZE)
		{
			write(1, buff, ptf->buff.pos);
			ptf->buff.read += ptf->buff.pos;
			ptf->buff.pos = 0;
			ft_bzero(buff, BUFF_SIZE + 1);
		}
		buff[ptf->buff.pos] = input[i];
		ptf->buff.pos++;
		size--;
		i++;
	}
	return (i);
}

void		buff_seqncat(t_ptf *ptf, char *input, long long n)
{
	int i;

	while (n)
	{
		i = 0;
		while (input[i])
		{
			ptf->buff.buff[ptf->buff.pos] = input[i];
			if (ptf->buff.pos == BUFF_SIZE)
			{
				if (write(1, ptf->buff.buff, ptf->buff.pos) < 0)
					exit(-1);
				ptf->buff.read += ptf->buff.pos;
				ptf->buff.pos = 0;
				ft_bzero(ptf->buff.buff, BUFF_SIZE + 1);
			}
			i++;
			ptf->buff.pos++;
		}
		n--;
	}
}
