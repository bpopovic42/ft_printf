/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_tests.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 14:38:49 by bopopovi          #+#    #+#             */
/*   Updated: 2018/06/12 02:00:55 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "acutest.h"
#include "ft_printf.h"

void	test_wc(void)
{
	char	*s1;
	wchar_t	lol;
	int		i;
	wchar_t	tmp[BUFF_SIZE / sizeof(wchar_t)];
	t_buff	buff;

	i = 0;
	lol = L'字';
	setlocale(P_ALL, "");
	ft_bzero(tmp, BUFF_SIZE);
	while (i < (BUFF_SIZE / sizeof(wchar_t)))
	{
		//i += sprintf(tmp + i, "%C", lol);
		tmp[i] = lol;
		i++;
		lol++;
	}
	tmp[BUFF_SIZE / sizeof(wchar_t) - 1] = '\0';

	printf("%S\n", tmp);

	ft_bzero(buff.buff, BUFF_SIZE);
	ptf_wcs((wchar_t*)tmp, &buff);
	printf("%s\n", buff.buff);
	TEST_CHECK_(ft_strcmp(tmp, buff.buff) == 0, "Expected %s got %s", tmp, buff.buff);
}

TEST_LIST = {
	{ "wc", test_wc },
	{ 0 }
};
