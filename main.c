/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 16:05:25 by bopopovi          #+#    #+#             */
/*   Updated: 2018/07/30 02:01:35 by bopopovi         ###   ########.fr       */
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

	wchar_t s[4];
		s[0] = 'a';
	s[1] = 250;
	s[2] = 'b';
	s[3] = '\0';

//	setlocale(LC_ALL, "en_US.UTF-8");
	frval = ft_printf("%-12ls F\n", s);
	prval = printf("%-12ls P\n", s);
	//frval = ft_printf("%-50.36ls F\n", L"°\)");
	//prval = printf("%-50.36ls P\n", L"°\)");
	//frval = ft_printf("%-50.36ls F\n", L"(╯°Д°）╯︵ /(.□ . \)");
	//prval = printf("%-50.36ls P\n", L"(╯°Д°）╯︵ /(.□ . \)");
	//frval = ft_printf("%C F\n", 0x4e6);
	//prval = printf("%C P\n", 0x4e6);
	//frval = ft_printf("%C F\n", L'💖');
	//prval = printf("%C P\n", L'💖');
	//frval = ft_printf("lool %d %10.4S F\n", 42, wcstest);
	//prval = printf("lool %d %10.4S P\n", 42, wcstest);
	//frval = ft_printf("{%3*d} F\n", 0, 0);
	//prval = printf("{%3*d} P\n", 0, 0);
	//frval = ft_printf("lol %d lala %C F\n", 42, -1);
	//prval = printf("lol %d lala %C P\n", 42, -1); // Problematic test case
	//frval = ft_printf("%");
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
