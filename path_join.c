/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_join.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:42:25 by junmlee           #+#    #+#             */
/*   Updated: 2024/06/29 15:47:47 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*path_join(char const *s1, char const *s2)
{
	unsigned int	s1_len;
	unsigned int	s2_len;
	char			*arr;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	arr = (char *)malloc(sizeof(char) * (s1_len + s2_len + 2));
	if (arr == NULL)
		return (NULL);
	ft_strlcpy(arr, s1, s1_len + 1);
	arr[s1_len] = '/';
	ft_strlcpy(arr + s1_len + 1, s2, s2_len + 1);
	arr[s1_len + s2_len + 1] = '\0';
	return (arr);
}
