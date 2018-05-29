/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 16:05:25 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/29 23:00:15 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

void	printf_tests();

int		main()
{
	char	*stest = "Hello";
	int		dtest = 1234;
	char	ctest = 'X';

	ft_printf("sdc", stest, dtest, ctest);

	ft_putchar('\n');

	printf_tests();

	return (0);
}

void	printf_tests()
{
	char *stest = "Hello";
	char *stest2 = "wassup ?";
	int		dtest = 1234;
	char	ctest = 'X';

	printf("%2$s %3$s", stest, stest2);

	(void)stest;
	(void)stest2;
	(void)dtest;
	(void)ctest;


}
