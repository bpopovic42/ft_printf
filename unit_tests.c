/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_tests.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 14:38:49 by bopopovi          #+#    #+#             */
/*   Updated: 2018/06/11 20:34:07 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "acutest.h"
#include "ft_printf.h"

void	test_wc(void)
{
	char	*s1;
	wchar_t	lol;
	int		i;
	char	tmp[BUFF_SIZE + 1];
	t_buff	buff;

	i = 0;
	lol = L'a';
	setlocale(P_ALL, "");
	while (i < BUFF_SIZE)
	{
		i += sprintf(tmp + i, "%C", lol);
		lol++;
	}
	tmp[BUFF_SIZE] = '\0';

	printf("X %s X", tmp);

	ft_bzero(buff.buff, BUFF_SIZE);
	ptf_wcs((wchar_t*)tmp, &buff);
	printf("%s", buff.buff);
	//TEST_CHECK_(ft_strcmp(s1, buff.buff) == 0, "Expected %s got %s", s1, buff.buff);
}

TEST_LIST = {
	{ "wc", test_wc },
	{ 0 }
};
