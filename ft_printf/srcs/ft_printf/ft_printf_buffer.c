/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_buffer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 18:48:52 by bopopovi          #+#    #+#             */
/*   Updated: 2018/07/28 20:36:32 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			buff_append(t_ptf *ptf, char *input, int size)
{
	int i;

	i = 0;
	if (ptf->buff.pos + size >= BUFF_SIZE)
	{
		write(1, ptf->buff.buff, ptf->buff.pos);
		ptf->buff.read += ptf->buff.pos;
		ptf->buff.pos = 0;
		ft_bzero(ptf->buff.buff, BUFF_SIZE + 1);
	}
	while (i < size)
	{
		ptf->buff.buff[ptf->buff.pos + i] = input[i];
		i++;
	}
	ptf->buff.pos += i;
	return (i);
}

int			buff_seqncat(t_ptf *ptf, char *input, int n)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (ptf->buff.pos + (ft_strlen(input) * n) >= BUFF_SIZE)
	{
		write(1, ptf->buff.buff, ptf->buff.pos);
		ptf->buff.read += ptf->buff.pos;
		ptf->buff.pos = 0;
		ft_bzero(ptf->buff.buff, BUFF_SIZE + 1);
	}
	while (n)
	{
		while (input[j])
		{
			ptf->buff.buff[ptf->buff.pos + i] = input[j];
			j++;
			i++;
		}
		j = 0;
		n--;
	}
	ptf->buff.pos += i;
	return (i);
}
