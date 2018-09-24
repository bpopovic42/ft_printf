/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 16:49:07 by bopopovi          #+#    #+#             */
/*   Updated: 2018/09/24 20:04:09 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <limits.h>
#include <float.h>
#include <locale.h>

static void		test_conversions(void)
{
	signed char sc;
	short shrt;
	int in;
	long lng;
	long long llng;
	intmax_t imt;

	sc = 0;
	shrt = 0;
	in = 0;
	lng = 0;
	llng = 0;
	imt = 0;
	setlocale(LC_ALL, "");
	printf("%d\n", printf("s = [ %ls ]", L"lol"));
	printf("%d\n", printf("d = [ %hd %hhd %d %ld %lld %jd %zd ]", SHRT_MAX,CHAR_MAX,INT_MAX,LONG_MAX,LLONG_MAX,LONG_MAX,INT_MAX));
	printf("%d\n", printf("u = [ %hhu %hu %lu %llu %ju %zu ]", UCHAR_MAX,USHRT_MAX,ULONG_MAX,ULLONG_MAX,ULONG_MAX,ULONG_MAX));
	printf("%d\n", printf("f = [ %f %lf ]", FLT_MAX,FLT_MAX));
	printf("%d\n", printf("e = [ %e %le ]", FLT_MAX,FLT_MAX));
	printf("%d\n", printf("g = [ %g %lg ]", FLT_MAX,FLT_MAX));
	printf("%d\n", printf("a = [ %a %la ]", FLT_MAX,FLT_MAX));
	printf("%d\n", printf("x = [ %hhx %hx %x %lx %llx %jx %zx ]", UCHAR_MAX,USHRT_MAX,UINT_MAX,ULONG_MAX,ULLONG_MAX,ULONG_MAX,UINT_MAX));
	printf("%d\n", printf("o = [ %hho %ho %o %lo %llo %jo %zo ]", UCHAR_MAX,USHRT_MAX,UINT_MAX,ULONG_MAX,ULLONG_MAX,ULONG_MAX,UINT_MAX));
	printf("%d\n", printf("S = [ %S ]", L"lol"));
	printf("%d\n", printf("c = [ %c %lc ]",'c','c'));
	printf("%d\n", printf("C = [ %C ]",L'C'));
	printf("%d\n", printf("n = [ %hhn %hn %n %ln %lln %jn %zn ]", &sc,&shrt,&in,&lng,&llng,&imt,&in));
	printf("%d\n", printf("p = [ %p ]", &in));
	printf("%d\n", printf("%% = [ %hh% %h% %% %l% %ll% %j% %z% ]"));
	printf("%d\n", printf("O = [ %hhO %hO %O %lO %llO %jO %zO ]", UCHAR_MAX,USHRT_MAX,UINT_MAX,ULONG_MAX,ULLONG_MAX,ULONG_MAX, UINT_MAX));
	printf("%d\n\n", printf("U = [ %hhU %hU %U %lU %llU %jU %zU ]", UCHAR_MAX,USHRT_MAX,UINT_MAX,ULONG_MAX,ULLONG_MAX,ULONG_MAX,UINT_MAX));

	ft_printf("%d\n", ft_printf("s = [ %ls ]", L"lol"));
	ft_printf("%d\n", ft_printf("d = [ %hd %hhd %d %ld %lld %jd %zd ]", SHRT_MAX,CHAR_MAX,INT_MAX,LONG_MAX,LLONG_MAX,LONG_MAX,INT_MAX));
	ft_printf("%d\n", ft_printf("u = [ %hhu %hu %lu %llu %ju %zu ]", UCHAR_MAX,USHRT_MAX,ULONG_MAX,ULLONG_MAX,ULONG_MAX,ULONG_MAX));
	ft_printf("%d\n", ft_printf("f = [ %f %lf ]", FLT_MAX,FLT_MAX));
	ft_printf("%d\n", ft_printf("e = [ %e %le ]", FLT_MAX,FLT_MAX));
	ft_printf("%d\n", ft_printf("g = [ %g %lg ]", FLT_MAX,FLT_MAX));
	ft_printf("%d\n", ft_printf("a = [ %a %la ]", FLT_MAX,FLT_MAX));
	ft_printf("%d\n", ft_printf("x = [ %hhx %hx %x %lx %llx %jx %zx ]", UCHAR_MAX,USHRT_MAX,UINT_MAX,ULONG_MAX,ULLONG_MAX,ULONG_MAX,UINT_MAX));
	ft_printf("%d\n", ft_printf("o = [ %hho %ho %o %lo %llo %jo %zo ]", UCHAR_MAX,USHRT_MAX,UINT_MAX,ULONG_MAX,ULLONG_MAX,ULONG_MAX,UINT_MAX));
	ft_printf("%d\n", ft_printf("S = [ %S ]", L"lol"));
	ft_printf("%d\n", ft_printf("c = [ %c %lc ]",'c','c'));
	ft_printf("%d\n", ft_printf("C = [ %C ]",L'C'));
	ft_printf("%d\n", ft_printf("n = [ %hhn %hn %n %ln %lln %jn %zn ]", &sc,&shrt,&in,&lng,&llng,&imt,&in));
	ft_printf("%d\n", ft_printf("p = [ %p ]", &in));
	ft_printf("%d\n", ft_printf("%% = [ %hh% %h% %% %l% %ll% %j% %z% ]"));
	ft_printf("%d\n", ft_printf("O = [ %hhO %hO %O %lO %llO %jO %zO ]", UCHAR_MAX,USHRT_MAX,UINT_MAX,ULONG_MAX,ULLONG_MAX,ULONG_MAX, UINT_MAX));
	ft_printf("%d\n\n", ft_printf("U = [ %hhU %hU %U %lU %llU %jU %zU ]", UCHAR_MAX,USHRT_MAX,UINT_MAX,ULONG_MAX,ULLONG_MAX,ULONG_MAX,UINT_MAX));
}

void	test_flags()
{
	signed char sc;
	short shrt;
	int in;
	long lng;
	long long llng;
	intmax_t imt;

	sc = 0;
	shrt = 0;
	in = 0;
	lng = 0;
	llng = 0;
	imt = 0;
	setlocale(LC_ALL, "");
	printf("%d\n", printf("s = [ %-10.10ls ]", L"lol"));
	printf("%d\n", printf("d = [ %-+10.10hd %-+10.10hhd %-+10.10d %-+10.10ld %-+10.10lld %-+10.10jd %-+10.10zd ]", SHRT_MAX,CHAR_MAX,INT_MAX,LONG_MAX,LLONG_MAX,LONG_MAX,INT_MAX));
	printf("%d\n", printf("u = [ %-10.10hhu %#10.10hu %#10.10lu %#10.10llu %#10.10ju %#10.10zu ]", UCHAR_MAX,USHRT_MAX,ULONG_MAX,ULLONG_MAX,ULONG_MAX,ULONG_MAX));
	printf("%d\n", printf("f = [ %#10.10f %#10.10lf ]", FLT_MAX,FLT_MAX));
	printf("%d\n", printf("e = [ %#10.10e %#10.10le ]", FLT_MAX,FLT_MAX));
	printf("%d\n", printf("g = [ %#10.10g %#10.10lg ]", FLT_MAX,FLT_MAX));
	printf("%d\n", printf("a = [ %#10.10a %#10.10la ]", FLT_MAX,FLT_MAX));
	printf("%d\n", printf("x = [ %#10.10hhx %#10.10hx %#10.10x %#10.10lx %#10.10llx %#10.10jx %#10.10zx ]", UCHAR_MAX,USHRT_MAX,UINT_MAX,ULONG_MAX,ULLONG_MAX,ULONG_MAX,UINT_MAX));
	printf("%d\n", printf("o = [ %#10.10hho %#10.10ho %#10.10o %#10.10lo %#10.10llo %#10.10jo %#10.10zo ]", UCHAR_MAX,USHRT_MAX,UINT_MAX,ULONG_MAX,ULLONG_MAX,ULONG_MAX,UINT_MAX));
	printf("%d\n", printf("S = [ %#10.10S ]", L"lol"));
	printf("%d\n", printf("c = [ %#10.10c %#10.10lc ]",'c','c'));
	printf("%d\n", printf("C = [ %#10.10C ]",L'C'));
	printf("%d\n", printf("n = [ %#10.10hhn %#10.10hn %#10.10n %#10.10ln %#10.10lln %#10.10jn %#10.10zn ]", &sc,&shrt,&in,&lng,&llng,&imt,&in));
	printf("%d\n", printf("p = [ %#10.10p ]", &in));
	printf("%d\n", printf("%% = [ %#10.10hh% %#10.10h% %#10.10% %#10.10l% %#10.10ll% %#10.10j% %#10.10z% ]"));
	printf("%d\n", printf("O = [ %#10.10hhO %#10.10hO %#10.10O %#10.10lO %#10.10llO %#10.10jO %#10.10zO ]", UCHAR_MAX,USHRT_MAX,UINT_MAX,ULONG_MAX,ULLONG_MAX,ULONG_MAX, UINT_MAX));
	printf("%d\n\n", printf("U = [ %#10.10hhU %#10.10hU %#10.10U %#10.10lU %#10.10llU %#10.10jU %#10.10zU ]", UCHAR_MAX,USHRT_MAX,UINT_MAX,ULONG_MAX,ULLONG_MAX,ULONG_MAX,UINT_MAX));

	ft_printf("%d\n", ft_printf("s = [ %-10.10ls ]", L"lol"));
	ft_printf("%d\n", ft_printf("d = [ %-+10.10hd %-+10.10hhd %-+10.10d %-+10.10ld %-+10.10lld %-+10.10jd %-+10.10zd ]", SHRT_MAX,CHAR_MAX,INT_MAX,LONG_MAX,LLONG_MAX,LONG_MAX,INT_MAX));
	ft_printf("%d\n", ft_printf("u = [ %-10.10hhu %#10.10hu %#10.10lu %#10.10llu %#10.10ju %#10.10zu ]", UCHAR_MAX,USHRT_MAX,ULONG_MAX,ULLONG_MAX,ULONG_MAX,ULONG_MAX));
	ft_printf("%d\n", ft_printf("f = [ %#10.10f %#10.10lf ]", FLT_MAX,FLT_MAX));
	ft_printf("%d\n", ft_printf("e = [ %#10.10e %#10.10le ]", FLT_MAX,FLT_MAX));
	ft_printf("%d\n", ft_printf("g = [ %#10.10g %#10.10lg ]", FLT_MAX,FLT_MAX));
	ft_printf("%d\n", ft_printf("a = [ %#10.10a %#10.10la ]", FLT_MAX,FLT_MAX));
	ft_printf("%d\n", ft_printf("x = [ %#10.10hhx %#10.10hx %#10.10x %#10.10lx %#10.10llx %#10.10jx %#10.10zx ]", UCHAR_MAX,USHRT_MAX,UINT_MAX,ULONG_MAX,ULLONG_MAX,ULONG_MAX,UINT_MAX));
	ft_printf("%d\n", ft_printf("o = [ %#10.10hho %#10.10ho %#10.10o %#10.10lo %#10.10llo %#10.10jo %#10.10zo ]", UCHAR_MAX,USHRT_MAX,UINT_MAX,ULONG_MAX,ULLONG_MAX,ULONG_MAX,UINT_MAX));
	ft_printf("%d\n", ft_printf("S = [ %#10.10S ]", L"lol"));
	ft_printf("%d\n", ft_printf("c = [ %#10.10c %#10.10lc ]",'c','c'));
	ft_printf("%d\n", ft_printf("C = [ %#10.10C ]",L'C'));
	ft_printf("%d\n", ft_printf("n = [ %#10.10hhn %#10.10hn %#10.10n %#10.10ln %#10.10lln %#10.10jn %#10.10zn ]", &sc,&shrt,&in,&lng,&llng,&imt,&in));
	ft_printf("%d\n", ft_printf("p = [ %#10.10p ]", &in));
	ft_printf("%d\n", ft_printf("%% = [ %#10.10hh% %#10.10h% %#10.10% %#10.10l% %#10.10ll% %#10.10j% %#10.10z% ]"));
	ft_printf("%d\n", ft_printf("O = [ %#10.10hhO %#10.10hO %#10.10O %#10.10lO %#10.10llO %#10.10jO %#10.10zO ]", UCHAR_MAX,USHRT_MAX,UINT_MAX,ULONG_MAX,ULLONG_MAX,ULONG_MAX, UINT_MAX));
	ft_printf("%d\n\n", ft_printf("U = [ %#10.10hhU %#10.10hU %#10.10U %#10.10lU %#10.10llU %#10.10jU %#10.10zU ]", UCHAR_MAX,USHRT_MAX,UINT_MAX,ULONG_MAX,ULLONG_MAX,ULONG_MAX,UINT_MAX));

}

void	test_bonuses(void)
{
	int test;
	char *str = "DAFUQ\n\n\t\0\0";

	test = LLONG_MAX;
	ft_printf("%b %#10.10b %#10.10hhb %B", test,test,test,test);
	ft_printf("%r %hhr %llr %#10.10r", str,str,str,str);
}

int		main(void)
{
	test_bonuses();
	return (0);
}
