/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:56:43 by junmlee           #+#    #+#             */
/*   Updated: 2024/06/28 18:34:47 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_hex(va_list *ap)
{
	unsigned int	n;
	int				len;
	const char		*base = "0123456789abcdef";
	char			*num_array;

	n = va_arg(*ap, unsigned int);
	len = check_len(n, 16);
	num_array = ft_utoa(n, len, 16, base);
	if (num_array == NULL)
		return (-1);
	else if (write(1, num_array, len) == -1)
	{
		free(num_array);
		return (-1);
	}
	else
	{
		free(num_array);
		return (len);
	}
}

int	print_hex_upper(va_list *ap)
{
	unsigned int	n;
	int				len;
	const char		*base_upper = "0123456789ABCDEF";
	char			*num_array;

	n = va_arg(*ap, unsigned int);
	len = check_len(n, 16);
	num_array = ft_utoa(n, len, 16, base_upper);
	if (num_array == NULL)
		return (-1);
	else if (write(1, num_array, len) == -1)
	{
		free(num_array);
		return (-1);
	}
	else
	{
		free(num_array);
		return (len);
	}
}
