/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 16:05:25 by bopopovi          #+#    #+#             */
/*   Updated: 2018/07/04 02:38:11 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/includes/ft_printf.h"
#include <wchar.h>
#include <stdio.h>
#include <unistd.h>
#include <locale.h>

void	printf_tests();
void	ptf_wc(wchar_t c);
void				stock_value(int value);

int		main()
{
	char	*stest = "Hello";
	int		dtest = -42;
	int64_t		lldtest = -42;
	long int	ldtest = 1231245124;
	char	ctest = 'X';
	double	dbltest = 1.234567;
	void	*ptrtest = &ctest;
	unsigned int	uitest = 1234;
	int		prval = 0;
	int		frval = 0;
	wchar_t	*wcstest = L"틯岭玈௠았♰蜱귯㽰";

	(void)stest;
	(void)dtest;
	(void)ctest;
	(void)ldtest;
	(void)wcstest;
	(void)lldtest;
	(void)dbltest;
	(void)ptrtest;
	(void)uitest;

	setlocale(LC_ALL, "");
	prval = printf("%2c 12p\n", 0);
	frval = ft_printf("%2c 12f\n", 0);
	printf("prval = %d, frval = %d\n", prval, frval);
	//printf(L"%C", wc); // Gives interesting compilation error
	return (0);
}

int		ft_pow(int nbr, int pow)
{
	while (pow--)
	{
		nbr *= nbr;
	}
	return (nbr);
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
