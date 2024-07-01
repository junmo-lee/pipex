/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:41:45 by junmlee           #+#    #+#             */
/*   Updated: 2024/07/01 22:35:52 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int warp_cmd_execve(t_cmd *cmd)
{
	return (execve(cmd->cmd_path, cmd->args, cmd->envp));
}

int	check_cmd_access(t_vars *vars, t_cmd *cmd)
{
	char	*temp;
	int		i;

	i = 0;
	while (vars->path[i] != NULL)
	{
		temp = path_join(vars->path[i], cmd->cmd_name);
		ft_printf("%s\n", temp);
		if (access(temp, X_OK) == 0)
		{
			ft_printf("%s\n", temp);
			cmd->cmd_path = temp;
			return (1);
		}
		free(temp);
		i++;
	}
	return (0);
}

void	do_pipex(t_vars *vars)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return ;
	else if (pid == 0)
	{
		close(vars->pipe_fd[1]);
		dup2(vars->pipe_fd[0], STDIN_FILENO);
		dup2(vars->file2_write_fd, STDOUT_FILENO);
		warp_cmd_execve(vars->cmd2);
	}
	else
	{
		close(vars->pipe_fd[0]);
		dup2(vars->file1_read_fd, STDIN_FILENO);
		dup2(vars->pipe_fd[1], STDOUT_FILENO);
		waitpid(pid, NULL, 0);
		warp_cmd_execve(vars->cmd1);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_vars	vars;

	init(&vars, argc, argv, envp);
	if (argc != 5)
		return (EXIT_FAILURE);
	vars.cmd1 = cmd_init(&vars, argv[2]);
	if (check_cmd_access(&vars, vars.cmd1))
		return (EXIT_FAILURE);
	vars.cmd2 = cmd_init(&vars, argv[3]);
	if (check_cmd_access(&vars, vars.cmd2))
		return (EXIT_FAILURE);
	pipe(vars.pipe_fd);
	vars.file1_read_fd = open(argv[1], O_RDONLY);
	vars.file2_write_fd = open(argv[4], O_WRONLY);
	if (vars.file1_read_fd == -1 || vars.file2_write_fd == -1)
		return (EXIT_FAILURE);
	do_pipex(&vars);
}
