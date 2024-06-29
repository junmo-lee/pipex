/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 21:44:59 by junmlee           #+#    #+#             */
/*   Updated: 2024/06/29 16:12:58 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include "./libft/libft.h"

int		ft_printf(const char *format, ...);
int		formatting(char type, va_list *ap);
int		print_char(va_list *ap);
int		print_string(va_list *ap);
int		print_dec(va_list *ap);
int		print_unsigned(va_list *ap);
int		print_hex(va_list *ap);
int		print_hex_upper(va_list *ap);
int		print_ptr(va_list *ap);

int		check_len(unsigned int n, int base_size);
char	*ft_utoa(unsigned int n, int len, int base_size, const char *base);


#endif