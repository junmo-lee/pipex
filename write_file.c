/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 22:13:32 by junmlee           #+#    #+#             */
/*   Updated: 2024/07/04 22:45:10 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	write_file(int *fd, char *file_path)
{
	*fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (access(file_path, F_OK) == 0)
	{
		if (access(file_path, W_OK) == 0)
			return (0);
		else
			write_stderr("Permission denied: ", file_path);
	}
	else
		write_stderr("No such file or directory: ", file_path);
	return (1);
}
