/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 15:28:14 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/30 17:26:17 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include "libft.h"
#include <stdarg.h>

int		ft_printf(const char * restrict format, ...);
t_list	*store_args(const char *restrict format, va_list ap);
int		parse_format(char **output, char *format, va_list ap, size_t *i_size, size_t *out_size);
size_t	parse_input(char **output, va_list ap, char *format);
int		fast_append(char **dst, char *app, size_t *dlen, size_t alen);


#endif
