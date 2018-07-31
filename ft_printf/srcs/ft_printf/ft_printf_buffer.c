/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_buffer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 18:48:52 by bopopovi          #+#    #+#             */
/*   Updated: 2018/07/31 02:48:37 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			buff_append(t_ptf *ptf, char *input, int size)
{
	int i;

	i = 0;
	while (size)
	{
		if (ptf->buff.pos == BUFF_SIZE)
		{
			write(1, ptf->buff.buff, ptf->buff.pos);
			ptf->buff.read += ptf->buff.pos;
			ptf->buff.pos = 0;
			ft_bzero(ptf->buff.buff, BUFF_SIZE + 1);
		}
		ptf->buff.buff[ptf->buff.pos] = input[i];
		ptf->buff.pos++;
		size--;
		i++;
	}
	return (i);
}

int			buff_seqncat(t_ptf *ptf, char *input, int n)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (n)
	{
		if (ptf->buff.pos + (ft_strlen(input)) >= BUFF_SIZE)
		{
			write(1, ptf->buff.buff, ptf->buff.pos);
			ptf->buff.read += ptf->buff.pos;
			ptf->buff.pos = 0;
			ft_bzero(ptf->buff.buff, BUFF_SIZE + 1);
		}
		while (input[j])
		{
			ptf->buff.buff[ptf->buff.pos + i] = input[j];
			j++;
			ptf->buff.pos++;
		}
		j = 0;
		n--;
	}
	return (i);
}
