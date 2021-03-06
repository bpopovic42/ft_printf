/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 12:37:34 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/30 17:47:25 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char *ptr;

	ptr = s1;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (n > ft_strlen(s2))
		return (NULL);
	while (*s1)
		s1++;
	while (*s2 && n--)
		*s1++ = *s2++;
	*s1 = '\0';
	return (ptr);
}
