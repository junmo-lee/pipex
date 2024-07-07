/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 22:37:45 by junmlee           #+#    #+#             */
/*   Updated: 2024/07/07 15:54:44 by junmlee          ###   ########.fr       */
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

void	write_stderr_exit(char *error_msg, char *name, int errorcode)
{
	ft_putstr_fd(error_msg, STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	exit(errorcode);
}

int	free_strs(char *strs[], int exit_code)
{
	size_t	i;
	char	**temp;

	if (strs == NULL)
		return (exit_code);
	i = 0;
	while (strs[i] != NULL)
	{
		ft_memset(strs[i], 0, ft_strlen(strs[i]));
		free(strs[i]);
		i++;
	}
	temp = strs;
	ft_memset(temp, 0, sizeof(temp));
	free(temp);
	return (exit_code);
}

void	free_cmds(t_cmd *cmd)
{
	char	*temp;

	ft_memset(cmd->cmd_name, 0, ft_strlen(cmd->cmd_name));
	free(cmd->cmd_name);
	free_strs(cmd->args, EXIT_SUCCESS);
	temp = cmd->cmd_path;
	ft_memset(cmd, 0, sizeof(t_cmd));
	free(cmd);
	if (temp == NULL)
		return ;
	ft_memset(temp, 0, ft_strlen(temp));
	free(temp);
}
