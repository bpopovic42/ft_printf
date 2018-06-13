/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_tests.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 14:38:49 by bopopovi          #+#    #+#             */
/*   Updated: 2018/06/13 15:54:20 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "acutest.h"
#include "ft_printf.h"
#include <locale.h>
#include <time.h>

#define RLEN 64

wchar_t* get_rand_wcs(size_t start, size_t end, wchar_t *ustr)
{
	size_t	interval_len;
	int		i;
	size_t	len = RLEN / sizeof(wchar_t);

	interval_len = end - start + 1;
	i = 0;
	srand(time(NULL));
	while (i < len)
	{
		ustr[i] = (rand() % interval_len) + start;
		i++;
	}
	ustr[len] = L'\0';
	return ustr;
}

void		test_randwcs(void)
{
	char		s1[RLEN + 1];
	char		s2[RLEN + 1];
	int			rval1;
	int			rval2;
	wchar_t		ustr[RLEN / sizeof(wchar_t) + 1];
	wchar_t		*test = get_rand_wcs(0x0000, 0xFFFF, ustr);

	setlocale(LC_ALL, "");
	ft_bzero(s1, RLEN + 1);
	ft_bzero(s2, RLEN + 1);
	rval1 = wcstombs(s1, test, RLEN + 1);
	rval2 = ft_wcstombs(s2, test, RLEN + 1);
	printf("%s", s1);
	TEST_CHECK_(ft_strcmp(s1, s2) == 0, "Expected %s got %s", s1, s2);
	TEST_CHECK_(rval1 == rval2, "Expected %d got %d", rval1, rval2);
}

void	test_wchar(void)
{
	wchar_t		*test = L"వ予s";
	int			rval1;
	int			rval2;
	char		s1[MB_LEN_MAX];
	char		s2[MB_LEN_MAX];

	setlocale(LC_ALL, "en_US.UTF-8");
	while (*test)
	{
		ft_bzero(s1, MB_LEN_MAX);
		ft_bzero(s2, MB_LEN_MAX);
		rval1 = wctomb(s1, *test);
		rval2 = ft_wctomb(s2, *test);
		TEST_CHECK_((ft_strcmp(s1, s2) == 0) && (rval1 == rval2),
			"Expected \"%s\" %d got \"%s\" %d", s1, rval1, s2, rval2);
		test++;
	}
	rval1 = wctomb(NULL, *test);
	rval2 = ft_wctomb(NULL, *test);
	TEST_CHECK_((ft_strcmp(s1, s2) == 0) && (rval1 == rval2),
		"Expected \"%s\" %d got \"%s\" %d", s1, rval1, s2, rval2);

}

TEST_LIST = {
	{ "randwcs", test_randwcs },
	{ "wchar", test_wchar },
	{ 0 }
};
