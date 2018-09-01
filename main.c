/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 16:05:25 by bopopovi          #+#    #+#             */
/*   Updated: 2018/09/01 18:23:52 by bopopovi         ###   ########.fr       */
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
	s[0] = 0x53;
	s[1] = 0xd800;
	s[2] = 0x81000;
	s[3] = '\0';

	setlocale(LC_ALL, "en_US.UTF-8");
	/*int lol = 0;
	while (lol < 100000)
	{
		frval = ft_printf("%8C et coco %C titi %lc F\n", 3250, 0x11f, 'a');
		//prval = printf("%8C et coco %C titi %lc P\n", 3250, 0x11f, 'a');
		frval = ft_printf("%-50.36ls F\n", L"°\)");
		//prval = printf("%-50.36ls P\n", L"°\)");
		frval = ft_printf("%-50.36ls F\n", L"(╯°Д°）╯︵ /(.□ . \)");
		//prval = printf("%-50.36ls P\n", L"(╯°Д°）╯︵ /(.□ . \)");
		frval = ft_printf("%C F\n", 0x4e6);
		//prval = printf("%C P\n", 0x4e6);
		frval = ft_printf("%C F\n", L'💖');
		//prval = printf("%C P\n", L'💖');
		frval = ft_printf("lool %d %10.4S F\n", 42, wcstest);
		//prval = printf("lool %d %10.4S P\n", 42, wcstest);
		frval = ft_printf("{%3*d} F\n", 0, 0);
		//prval = printf("{%3*d} P\n", 0, 0);
		frval = ft_printf("lol %d lala %C F\n", 42, -1);
		//prval = printf("lol %d lala %C P\n", 42, -1); // Problematic test case
		frval = ft_printf("%");
	}*/
	//ft_printf("%f F\n", -1 / 0.45);
	//printf("%f P\n", test.nbr);
	//printf("prval = %d, frval = %d\n", prval, frval);
	t_dbl test;
	test.bits.mant = 954;
	test.bits.expn = 100;
	test.val = 1;
	//frval = ft_printf("%.201g\n%.201e\n%.201f F\n", test.val, test.val, test.val);
	//prval = printf("%.201g\n%.201e\n%.201f P\n", test.val, test.val, test.val);
	int fnts = 0;
	int pnts = 0;
	frval = ft_printf("%.16g F\n", test.val);
	prval = printf("%.16g P\n", test.val);
	printf("prval = %d, frval = %d\n", prval, frval);
	printf("pnts = %d, fnts = %d\n", pnts, fnts);
	//printf(L"%C", wc); // Gives interesting compilation error
	//frval = ft_printf("lol %lq F\n", &fnts); // Seems strange that
	//prval = printf("lol %lq P\n", &pnts); // I do write invalid specifier
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
