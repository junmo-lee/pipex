/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:59:53 by junmlee           #+#    #+#             */
/*   Updated: 2024/07/22 17:19:03 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	write_file(int *fd, char *file_path, int option)
{
	*fd = open(file_path, option, 0644);
	if (access(file_path, F_OK) == 0)
	{
		if (access(file_path, W_OK) == 0)
			return ;
		else
			write_stderr("Permission denied: ", file_path);
	}
	else
		write_stderr("No such file or directory: ", file_path);
}
