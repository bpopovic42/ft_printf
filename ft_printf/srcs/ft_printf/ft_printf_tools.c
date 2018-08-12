/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 17:11:54 by bopopovi          #+#    #+#             */
/*   Updated: 2018/08/13 00:51:03 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf_is_flag(int c)
{
	return (ft_isdigit(c) || c == '-' || c == '+' || c == '#' || c == '.'
		|| c == 'h' || c == 'j' || c == 'l' || c == 'z' || c == ' '
			|| c == '*');
}

int			ft_printf_is_spec(int c)
{
	return (c == 's' || c == 'S' || c == 'p' || c == 'd' || c == 'D' || c == 'i'
			|| c == 'o' || c == 'O' || c == 'u' || c == 'U' || c == 'x'
				|| c == 'X' || c == 'c' || c == 'C' || c == 'f' || c == 'F'
					|| c == '%');
}

size_t		ft_printf_atoi(const char *str, int *res)
{
	int			flag;
	size_t		i;

	i = 0;
	*res = 0;
	while (ft_isspace(str[i]))
		i++;
	flag = str[i] == '-' ? -1 : 1;
	i += str[i] == '-' || str[i] == '+' ? 1 : 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		*res = (*res * 10) + (str[i++] - '0');
	*res *= flag;
	return (i);
}

static long long	bdiv(long long dvd, long long dvs)
{
	long long q;
	long long r;
	int i;

	q = 0;
	i = 59;
	while (i >= 0)
	{
		r = (dvs << i);
		if (r < LLONG_MAX && r >= 0)
		{
			if (r <= dvd)
			{
				q |= (1LL << i);
				dvd -= r;
			}
		}
		i--;
	}
	return (q);
}

int			ft_printf_itoa_base(char *buff, char *charset, long long nbr)
{
	int		base;
	int		i;
	char	*ptr;
	int		max;

	i = 0;
	ptr = buff;
	base = ft_strlen(charset);
	if (base > 16 || base < 2 || !ptr)
		return (-1);
	max = nbr == LLONG_MIN ? 1 : 0;
	*ptr = nbr < 0 ? '-' : '+';
	nbr = nbr == LLONG_MIN ? 9223372036854775807 : nbr;
	nbr *= nbr < 0 ? -1 : 1;
	ptr++;
	while (nbr || i < 1)
	{
		ptr[i] = charset[nbr % base];
		i++;
		nbr = bdiv(nbr, base);
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
