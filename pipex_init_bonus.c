/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:58:43 by junmlee           #+#    #+#             */
/*   Updated: 2024/07/21 19:06:14 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

int	get_pwd(t_vars *vars)
{
	int		i;

	i = 0;
	while (vars->envp[i] != NULL)
	{
		if (ft_strncmp(vars->envp[i], "PWD=", 4) == 0)
		{
			vars->pwd = ft_substr(vars->envp[i], 4, ft_strlen(vars->envp[i]));
			if (vars->pwd == NULL)
				exit(EXIT_FAILURE);
			return (0);
		}
		i++;
	}
	return (1);
}

void	init(t_vars *vars, int argc, char *argv[], char *envp[])
{
	ft_memset(vars, 0, sizeof(vars));
	vars->argc = argc;
	vars->argv = argv;
	vars->envp = envp;
	if (import_path(vars) == 1)
		exit(EXIT_FAILURE);
	if (get_pwd(vars) == 1)
		exit(EXIT_FAILURE);
}

t_cmd	*cmd_init(t_vars *vars, int count, char *cmd_argv)
{
	t_cmd	*ret;

	ret = malloc(sizeof(t_cmd));
	if (ret == NULL)
		exit(EXIT_FAILURE);
	ft_memset(ret, 0, sizeof(t_cmd));
	ret->envp = vars->envp;
	ret->cmd_argv = ft_strdup(cmd_argv);
	parse_name_args(ret, cmd_argv);
	if (count != vars->cmd_len - 1)
	{
		if (pipe(vars->pipe_fd) == -1)
			exit(EXIT_FAILURE);
		vars->next_write = dup(vars->pipe_fd[1]);
		close(vars->pipe_fd[1]);
	}
	else
	{
		vars->next_write = dup(vars->file2_write_fd);
		close(vars->file2_write_fd);
	}
	return (ret);
}
