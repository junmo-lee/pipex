/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 21:48:36 by junmlee           #+#    #+#             */
/*   Updated: 2024/06/28 18:35:29 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	formatting(char type, va_list *ap)
{
	if (type == 'c')
		return (print_char(ap));
	else if (type == 's')
		return (print_string(ap));
	else if (type == 'p')
		return (print_ptr(ap));
	else if (type == 'd' || type == 'i')
		return (print_dec(ap));
	else if (type == 'u')
		return (print_unsigned(ap));
	else if (type == 'x')
		return (print_hex(ap));
	else if (type == 'X')
		return (print_hex_upper(ap));
	else if (type == '%')
	{
		if (write(1, "%", 1) == -1)
			return (-1);
		else
			return (1);
	}
	else
		return (-1);
}

int	va_end_ret(va_list *ap, int ret)
{
	va_end(*ap);
	return (ret);
}

int	ft_printf(const char *format, ...)
{
	int		len;
	int		i;
	int		ret_formatting;
	va_list	ap;

	if (format == NULL)
		return (-1);
	va_start(ap, format);
	len = 0;
	i = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
			ret_formatting = formatting(format[i++ + 1], &ap);
		else
			ret_formatting = write(1, format + i, 1);
		if (ret_formatting == -1)
			return (va_end_ret(&ap, -1));
		len += ret_formatting;
		i++;
	}
	return (va_end_ret(&ap, len));
}
