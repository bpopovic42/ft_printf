/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 17:11:54 by bopopovi          #+#    #+#             */
/*   Updated: 2018/08/11 01:48:47 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf_is_flag(char c)
{
	return (ft_isdigit(c) || c == '-' || c == '+' || c == '#' || c == '.'
		|| c == 'h' || c == 'j' || c == 'l' || c == 'z' || c == ' '
			|| c == '%' || c == '*');
}

int			ft_printf_is_fspecif(int c)
{
	return (c == 's' || c == 'S' || c == 'p' || c == 'd' || c == 'D' || c == 'i'
			|| c == 'o' || c == 'O' || c == 'u' || c == 'U' || c == 'x'
				|| c == 'X' || c == 'c' || c == 'C' || c == 'f' || c == 'F'
					|| c == 'g' || c == 'G' || c == 'e'
						|| c == 'E' || c == '%');
}

int			ft_printf_itoa_base(char *buff, char *charset, long long nbr)
{
	int		base;
	int		i;
	char	*ptr;
	int		max;

	i = 0;
	max = nbr == LLONG_MIN ? 1 : 0;
	ptr = buff;
	base = ft_strlen(charset);
	*ptr = nbr < 0 ? '-' : '+';
	nbr = nbr == LLONG_MIN ? 9223372036854775807 : nbr;
	nbr *= nbr < 0 ? -1 : 1;
	if (base > 16 || base < 2 || !ptr)
		return (-1);
	ptr++;
	while (nbr || i < 1)
	{
		ptr[i] = charset[nbr % base];
		i++;
		nbr /= base;
	}
	ptr[0] += max;
	ptr[i] = '\0';
	ptr = ft_strrev(ptr);
	return (i);
}

int			ft_printf_uitoa_base(char *buff, char *charset, uint64_t nbr)
{
	int		base;
	int		i;
	char	*ptr;

	i = 0;
	ptr = buff;
	base = ft_strlen(charset);
	*ptr = '+';
	ptr++;
	if (base > 16 || base < 2)
		return (-1);
	while (nbr || i < 1)
	{
		ptr[i] = charset[nbr % base];
		i++;
		nbr /= base;
	}
	ptr[i] = '\0';
	ptr = ft_strrev(ptr);
	return (i);
}

void			dump_fmt(t_ptf *ptf)
{
	buff_append(ptf, (char*)FMT, INDEX);
	FMT += INDEX;
	INDEX = 0;
}
