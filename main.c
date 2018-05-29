/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 16:05:25 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/29 16:07:09 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		main()
{
	char	*stest = "Hello";
	int		dtest = 1234;
	char	ctest = 'X';

	ft_printf("sdc", stest, dtest, ctest);

	return (0);
}
