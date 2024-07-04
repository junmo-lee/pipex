/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 21:57:54 by junmlee           #+#    #+#             */
/*   Updated: 2024/07/04 22:45:05 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	read_file(int *fd, char *file_path)
{
	*fd = open(file_path, O_RDONLY);
	if (access(file_path, F_OK) == 0)
	{
		if (access(file_path, R_OK) == 0)
			return (0);
		else
			write_stderr("Permission denied: ", file_path);
	}
	else
		write_stderr("No such file or directory: ", file_path);
	return (1);
}
