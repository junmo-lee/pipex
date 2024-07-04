/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 22:37:45 by junmlee           #+#    #+#             */
/*   Updated: 2024/07/04 22:41:36 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	write_stderr(char *error_msg, char *name)
{
	ft_putstr_fd(error_msg, STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (0);
}

int	write_stderr_exit(char *error_msg, char *name, int errorcode)
{
	ft_putstr_fd(error_msg, STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	exit(errorcode);
}
