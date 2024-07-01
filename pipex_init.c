/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 20:22:05 by junmlee           #+#    #+#             */
/*   Updated: 2024/07/01 22:35:31 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	import_path(t_vars *vars)
{
	char	*temp;

	while (*(vars->envp) != NULL)
	{
		if (ft_strncmp(*(vars->envp), "PATH=", 5) == 0)
		{
			vars->path = ft_split(*(vars->envp), ':');
			if (vars->path == NULL)
				return (1);
			temp = vars->path[0];
			vars->path[0] = ft_substr(temp, 5, ft_strlen(temp));
			ft_memset(temp, 0, ft_strlen(temp));
			free(temp);
			return (0);
		}
		(vars->envp)++;
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

//cmd 의 전체 ex) ls -al : full_cmd
//cmd_name 은 각 path 와 더해져서 access 확인
//전체를 cmd->args (execve 의 argv 에 들어갈거)
int	parse_name_args(t_cmd *cmd, char *cmd_argv)
{
	char	**temp;
	size_t	argc;

	temp = ft_split(cmd_argv, ' ');
	if (temp == NULL)
		return (1);
	cmd->cmd_name = *(temp);
	argc = 0;
	while (temp[argc] != NULL)
		argc++;
	cmd->args = malloc(sizeof(char *) * (argc + 1));
	if (cmd->args == NULL)
		return (1);
	argc = 0;
	while (temp[argc] != NULL)
	{
		cmd->args[argc] = temp[argc];
		argc++;
	}
	cmd->args[argc] = NULL;
	free(temp);
	return (0);
}

t_cmd	*cmd_init(t_vars *vars, char *cmd_argv)
{
	t_cmd	*ret;

	ret = malloc(sizeof(t_cmd));
	if (ret == NULL)
		return (NULL);
	ft_memset(ret, 0, sizeof(t_cmd));
	ret->envp = vars->envp;
	parse_name_args(ret, cmd_argv);
	return (ret);
}
