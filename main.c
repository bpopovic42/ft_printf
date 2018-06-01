/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 16:05:25 by bopopovi          #+#    #+#             */
/*   Updated: 2018/06/01 22:08:59 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <wchar.h>
#include <stdio.h>

void	printf_tests();

int		main()
{
	/*char	*stest = "Hello";
	int		dtest = 1234;
	char	ctest = 'X';*/

	//ft_printf("1st spec : %d and 2nd spec : %d");
	//ft_printf("1st spec : %d and 2nd spec : %d", 10, 9);
	wchar_t wc = 'Ʃ';
	printf("%c", wc);

	ft_putchar('\n');

	//printf_tests();

	return (0);
}

void	printf_tests()
{
	char *stest = "Hello";
	char *stest2 = "wassup ?";
	int		dtest = 1234;
	char	ctest = 'X';

	//printf("%2$s %3$s", stest, stest2);

	(void)stest;
	(void)stest2;
	(void)dtest;
	(void)ctest;


}
