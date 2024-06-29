/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_dec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:50:34 by junmlee           #+#    #+#             */
/*   Updated: 2024/06/28 18:34:38 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_dec(va_list *ap)
{
	int		n;
	ssize_t	ret_write;
	char	*num_array;

	n = va_arg(*ap, int);
	num_array = ft_itoa(n);
	if (num_array == NULL)
		return (-1);
	ret_write = write(1, num_array, ft_strlen(num_array));
	free(num_array);
	num_array = NULL;
	if (ret_write == -1)
		return (-1);
	else
		return (ret_write);
}

int	print_unsigned(va_list *ap)
{
	unsigned int	n;
	int				len;
	const char		*base = "0123456789";
	char			*num_array;

	len = 0;
	n = va_arg(*ap, unsigned int);
	len = check_len(n, 10);
	num_array = ft_utoa(n, len, 10, base);
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
