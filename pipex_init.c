/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 20:22:05 by junmlee           #+#    #+#             */
/*   Updated: 2024/07/06 22:05:20 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	import_path(t_vars *vars)
{
	char	*temp;
	int		i;

	i = 0;
	while (vars->envp[i] != NULL)
	{
		if (ft_strncmp(vars->envp[i], "PATH=", 5) == 0)
		{
			vars->path = ft_split(vars->envp[i], ':');
			if (vars->path == NULL)
				exit(EXIT_FAILURE);
			temp = vars->path[0];
			vars->path[0] = ft_substr(temp, 5, ft_strlen(temp));
			ft_memset(temp, 0, ft_strlen(temp));
			free(temp);
			return (0);
		}
		i++;
	}
	return (1);
}

int	init(t_vars *vars, int argc, char *argv[], char *envp[])
{
	ft_memset(vars, 0, sizeof(vars));
	vars->argc = argc;
	vars->argv = argv;
	vars->envp = envp;
	import_path(vars);
	return (0);
}

int	parse_name_args(t_cmd *cmd, char *cmd_argv)
{
	char	**temp;

	temp = ft_split(cmd_argv, ' ');
	if (temp == NULL)
		exit(EXIT_FAILURE);
	cmd->cmd_name = ft_strdup(*temp);
	cmd->args = temp;
	//system("leaks debug.out");
	return (0);
}

void	check_cmd_access(t_vars *vars, t_cmd *cmd)
{
	char	*temp;
	int		i;

	i = 0;
	while (vars->path[i] != NULL)
	{
		temp = path_join(vars->path[i], cmd->cmd_name);
		if (temp == NULL)
			exit(EXIT_FAILURE);
		if (access(temp, F_OK) == 0)
		{
			cmd->cant_execute = 1;
			if (access(temp, X_OK) == 0)
			{
			// ft_putstr_fd(temp, STDERR_FILENO);
			// ft_putchar_fd('\n', STDERR_FILENO);
				cmd->cmd_path = temp;
				return ;
			}
		}
		free(temp);
		i++;
	}
	if (cmd->cant_execute)
		write_stderr_exit("permission denied: ", cmd->cmd_name, 126);
	else
		write_stderr_exit("command not found: ", cmd->cmd_name, 127);
}

t_cmd	*cmd_init(t_vars *vars, char *cmd_argv)
{
	t_cmd	*ret;

	ret = malloc(sizeof(t_cmd));
	if (ret == NULL)
		exit(EXIT_FAILURE);
	ft_memset(ret, 0, sizeof(t_cmd));
	ret->envp = vars->envp;
	parse_name_args(ret, cmd_argv);
	return (ret);
}
