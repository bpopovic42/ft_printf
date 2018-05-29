/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 15:28:14 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/29 17:39:01 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include "libft.h"
#include <stdarg.h>

int		ft_printf(const char * restrict format, ...);
t_list	*store_args(const char *restrict format, va_list ap);

#endif
