/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 15:28:14 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/30 19:35:19 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include "libft.h"
#include <stdarg.h>
#include <unistd.h>

int		ft_printf(const char * restrict format, ...);
t_list	*store_args(const char *restrict format, va_list ap);
int		parse_format(char **output, char **format, va_list ap, size_t *in_len, size_t *out_len);
size_t	parse_format_string(char **output, va_list ap, char *fmt);
int		fast_append(char **dst, char **app, size_t *dlen, size_t *alen);
int		get_format_arg(char *format, char **output, va_list ap);


#endif
