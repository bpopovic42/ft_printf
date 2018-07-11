/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_buffer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 18:48:52 by bopopovi          #+#    #+#             */
/*   Updated: 2018/07/11 21:12:21 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			buff_append(t_buff *buff, char *input, int size)
{
	int i;

	i = 0;
	if (buff->pos + size >= BUFF_SIZE)
	{
		write(1, buff->buff, buff->pos);
		buff->read += buff->pos;
		buff->pos = 0;
		ft_bzero(buff->buff, BUFF_SIZE + 1);
	}
	while (i < size)
	{
		buff->buff[buff->pos + i] = input[i];
		i++;
	}
	buff->pos += i;
	return (i);
}
