/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_buffer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 18:48:52 by bopopovi          #+#    #+#             */
/*   Updated: 2018/08/30 18:42:52 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	local_putnbr_octal(t_ptf *ptf, char value)
{
	char	tmp[4];
	int		i;

	i = 0;
	while (value)
	{
		tmp[i] = value % 8 + '0';
		value /= 8;
		i++;
	}
	tmp[i] = '\\';
	while (i >= 0)
	{
		if (ptf->buff.pos == FT_PRINTF_BUFF_SIZE)
		{
			if (write(1, ptf->buff.buff, ptf->buff.pos) < 0)
				exit(-1);
			ptf->buff.read += ptf->buff.pos;
			ptf->buff.pos = 0;
		}
		ptf->buff.buff[ptf->buff.pos] = tmp[i];
		ptf->buff.pos++;
		i--;
	}
	return (i);
}

void		ft_printf_buff_cat_npr(t_ptf *ptf, char *input, int size)
{
	int		i;
	char	*buff;

	i = 0;
	buff = ptf->buff.buff;
	while (size)
	{
		if (ptf->buff.pos == FT_PRINTF_BUFF_SIZE)
		{
			if (write(1, buff, ptf->buff.pos) < 0)
				exit(-1);
			ptf->buff.read += ptf->buff.pos;
			ptf->buff.pos = 0;
		}
		if (input[i] > 31)
			buff[ptf->buff.pos] = input[i];
		else
			ptf->buff.pos += local_putnbr_octal(ptf, input[i]);
		ptf->buff.pos++;
		size--;
		i++;
	}
}

void		ft_printf_buff_cat(t_ptf *ptf, char *input, int size)
{
	int		i;
	char	*buff;

	i = 0;
	buff = ptf->buff.buff;
	while (size)
	{
		if (ptf->buff.pos == FT_PRINTF_BUFF_SIZE)
		{
			if (write(1, buff, ptf->buff.pos) < 0)
				exit(-1);
			ptf->buff.read += ptf->buff.pos;
			ptf->buff.pos = 0;
		}
		buff[ptf->buff.pos] = input[i];
		ptf->buff.pos++;
		size--;
		i++;
	}
}

void		ft_printf_buff_catn(t_ptf *ptf, char *input, long long n)
{
	int len;

	len = ft_strlen(input);
	while (n--)
		ft_printf_buff_cat(ptf, input, len);
}

void			ft_printf_dump_fmt(t_ptf *ptf)
{
	ft_printf_buff_cat(ptf, (char*)ptf->fmt.format, ptf->fmt.i);
	ptf->fmt.format += ptf->fmt.i;
	ptf->fmt.i = 0;
}
