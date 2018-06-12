/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_tests.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 14:38:49 by bopopovi          #+#    #+#             */
/*   Updated: 2018/06/12 18:37:42 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "acutest.h"
#include "ft_printf.h"
#include <time.h>

wchar_t* get_rand_wcs(size_t start, size_t end, wchar_t *ustr)
{
	size_t	interval_len;
	int		i;
	size_t	len = BUFF_SIZE / sizeof(wchar_t);

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

void	test_randwcs(void)
{
	char		s1[BUFF_SIZE + 1];
	t_buff		buff;
	wchar_t		ustr[BUFF_SIZE / sizeof(wchar_t) + 1];
	wchar_t		*test = get_rand_wcs(0x0000, 0xFFFF, ustr);

	setlocale(P_ALL, "");
	init_buffer(&buff);
	ft_bzero(s1, BUFF_SIZE + 1);
	wcstombs(s1, test, BUFF_SIZE + 1);
	ptf_wcs(test, &buff);
	printf("%S", test);
	TEST_CHECK_(ft_strcmp(s1, buff.buff) == 0, "Expected %s got %s", s1, buff.buff);
}

void	test_wchar(void)
{
	wchar_t		test = L'వ';
	char		s[MB_LEN_MAX];
	t_buff		buff;

	setlocale(P_ALL, "");
	init_buffer(&buff);
	ft_bzero(s, MB_LEN_MAX);
	wctomb(s, test);
	ft_wctomb(buff.buff, test);
	TEST_CHECK_(ft_strcmp(s, buff.buff) == 0, "Expected %s got %s", s, buff.buff);
}

TEST_LIST = {
	//{ "randwcs", test_randwcs },
	{ "wchar", test_wchar },
	{ 0 }
};
