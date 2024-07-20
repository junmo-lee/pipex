/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:59:30 by junmlee           #+#    #+#             */
/*   Updated: 2024/07/20 21:42:36 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	ft_memset(cmd->cmd_name, 0, ft_strlen(cmd->cmd_name));
	free(cmd->cmd_name);
	free_strs(cmd->args, EXIT_SUCCESS);
	// ft_memset(cmd, 0, sizeof(t_cmd));
	// free(cmd);
	if (cmd->cmd_path == NULL)
		return ;
	ft_memset(cmd->cmd_path, 0, ft_strlen(cmd->cmd_path));
	free(cmd->cmd_path);
}

char	**pipex_split(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
		{
			if (i != 0 && str[i - 1] == '\\')
			{
				str[i - 1] = 1;
				str[i++] = '\'';
			}
			else
				str[i++] = 1;
			while (str[i] != '\0' && str[i] != '\'')
				i++;
			if (str[i - 1] == '\\')
				str[i - 1] = '\'';
			str[i++] = 1;
		}
		if (str[i] == c)
			str[i] = 1;
		i++;
	}
	return (ft_split(str, 1));
}
