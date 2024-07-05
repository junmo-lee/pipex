/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 22:29:26 by junmlee           #+#    #+#             */
/*   Updated: 2023/11/19 15:16:50 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_len(unsigned int n, int base_size)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= base_size;
		i++;
	}
	return (i);
}

char	*ft_utoa(unsigned int n, int len, int base_size, const char *base)
{
	char	*arr;

	if (n == 0)
		return (ft_strdup("0"));
	arr = malloc(sizeof(char) * (len + 1));
	if (arr == NULL)
		return (NULL);
	while (len--)
	{
		arr[len] = base[n % base_size];
		n /= base_size;
	}
	return (arr);
}
