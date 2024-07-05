/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 22:37:45 by junmlee           #+#    #+#             */
/*   Updated: 2024/07/05 16:58:56 by junmlee          ###   ########.fr       */
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

void	free_strs(char *strs[])
{
	size_t	i;

	i = 0;
	while (strs[i] != NULL)
	{
		ft_memset(strs[i], 0, ft_strlen(strs[i]));
		free(strs[i]);
		i++;
	}
}

void	free_cmds(t_cmd *cmd)
{
	ft_memset(cmd->cmd_path, 0, ft_strlen(cmd->cmd_path));
	free(cmd->cmd_path);
	free_strs(cmd->args);
	ft_memset(cmd->cmd_name, 0, ft_strlen(cmd->cmd_name));
	free(cmd->cmd_name);
}
