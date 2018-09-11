/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 14:47:35 by bopopovi          #+#    #+#             */
/*   Updated: 2018/09/11 16:48:09 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		main(void)
{
	float test = 500000099999999999999.0;
	int ret;

	(void)ret;
	ret = ft_printf("%.100g F\n", test);
	printf("%.100g P\n\n", test);

	ret = ft_printf("%.100e F\n", test);
	printf("%.100e P\n\n", test);

	ret = ft_printf("%.100f F\n", test);
	printf("%.100f P\n\n", test);

	ret = ft_printf("%.100a F\n", test);
	printf("%.100a P\n", test);
	return (0);
}
