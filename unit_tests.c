/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_tests.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 14:38:49 by bopopovi          #+#    #+#             */
/*   Updated: 2018/06/12 22:31:34 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "acutest.h"
#include "ft_printf.h"
#include <time.h>

#define RLEN 4

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
	wchar_t		ustr[RLEN / sizeof(wchar_t) + 1];
	wchar_t		*test = get_rand_wcs(0x0000, 0xFFFF, ustr);

	setlocale(P_ALL, "");
	ft_putnbr(printf("%S", test));
	ft_putchar('\n');
	ft_bzero(s1, RLEN + 1);
	ft_bzero(s2, RLEN + 1);
	/*ft_putnbr(wcstombs(s1, test, RLEN + 1));
	ft_putchar('\n');
	ft_putnbr(ft_wcstombs(s2, test, RLEN + 1));
	ft_putchar('\n');*/
	wcstombs(s1, test, RLEN + 1);
	ft_wcstombs(s2, test, RLEN + 1);
	printf("%d ", test[0]);
	TEST_CHECK_(ft_strcmp(s1, s2) == 0, "Expected %s got %s", s1, s2);
}

void	test_wchar(void)
{
	//wchar_t		test = L'వ';
	//wchar_t		test = L'予';
	wchar_t		test = 1573160560;
	//wchar_t		test = L's';
	char		s[MB_LEN_MAX];
	t_buff		buff;

	setlocale(P_ALL, "");
	init_buffer(&buff);
	ft_bzero(s, MB_LEN_MAX);
	wctomb(s, test);
	ft_wctomb(buff.buff, test);
	/*printf("%u %u", (unsigned int)s, (unsigned int)buff.buff);
	printf("%u ", (unsigned int)test);
	printf("%hhu %hhu\n", (unsigned char)s[0], (unsigned char)buff.buff[0]);
	printf("%hhu %hhu\n", (unsigned char)s[1], (unsigned char)buff.buff[1]);
	printf("%hhu %hhu\n", (unsigned char)s[2], (unsigned char)buff.buff[2]);
	printf("%hhu %hhu\n", (unsigned char)s[3], (unsigned char)buff.buff[3]);*/
	TEST_CHECK_(ft_strcmp(s, buff.buff) == 0, "Expected %s got %s", s, buff.buff);
}

TEST_LIST = {
	{ "randwcs", test_randwcs },
	{ "wchar", test_wchar },
	{ 0 }
};
