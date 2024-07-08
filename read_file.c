/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 21:57:54 by junmlee           #+#    #+#             */
/*   Updated: 2024/07/08 22:04:54 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	read_file(int *fd, char *file_path, int option)
{
	*fd = open(file_path, option);
	if (access(file_path, F_OK) == 0)
	{
		if (access(file_path, R_OK) == 0)
			return ;
		else
			write_stderr("Permission denied: ", file_path);
	}
	else
		write_stderr("No such file or directory: ", file_path);
}
