/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 17:11:54 by bopopovi          #+#    #+#             */
/*   Updated: 2018/08/29 02:39:45 by bopopovi         ###   ########.fr       */
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
					|| c == 'b' || c == 'B' || c == '%' || c == 'e'
						|| c == 'E' || c == 'g' || c == 'G' || c == 'n'
							|| c == 'a' || c == 'A' || c == 'r');
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

int			ft_printf_itoa_base(char *buff, char *charset, long long nbr)
{
	int		base;
	int		i;
	char	*ptr;
	unsigned long long tmp;

	i = 0;
	ptr = buff;
	base = ft_strlen(charset);
	if (base > 16 || base < 2 || !ptr)
		return (-1);
	*ptr = nbr < 0 ? '-' : '+';
	tmp = (unsigned long long)nbr * (*ptr == '-' ? -1 : 1);
	ptr++;
	while (tmp || i < 1)
	{
		ptr[i] = charset[tmp % base];
		i++;
		tmp /= base;
	}
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
