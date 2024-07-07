/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:25:26 by junmlee           #+#    #+#             */
/*   Updated: 2024/07/07 16:22:50 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(t_vars *vars, t_cmd *cmd[], int count)
{
	check_cmd_access(vars, cmd[count]);
	if (count == 0)
	{
		if (dup2(vars->file1_read_fd, STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
		dup2(vars->file1_read_fd, STDIN_FILENO);
	}
	else
		dup2(cmd[count - 1]->pipe_fd[0], STDIN_FILENO);
	if (count != vars->argc - 4)
		dup2(cmd[count]->pipe_fd[1], STDOUT_FILENO);
	else
	{
		if (dup2(vars->file2_write_fd, STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
	}
	if (count != vars->argc - 4)
		close(cmd[count]->pipe_fd[0]);
	execve(cmd[count]->cmd_path, cmd[count]->args, cmd[count]->envp);
}

void	do_pipex(t_vars *vars, t_cmd *cmd[])
{
	int		count;
	pid_t	fork_ret;

	count = 0;
	while (count < vars->argc - 3)
	{
		cmd[count] = cmd_init(vars, vars->argv[count + 2]);
		if (count != vars->argc - 4)
			if (pipe(cmd[count]->pipe_fd) == -1)
				exit(EXIT_FAILURE);
		fork_ret = fork();
		if (fork_ret == -1)
			exit(EXIT_FAILURE);
		else if (fork_ret == 0)
			child(vars, cmd, count);
		else
		{
			cmd[count]->pid = fork_ret;
			if (count != 0)
				close(cmd[count - 1]->pipe_fd[0]);
			if (count != vars->argc - 4)
				close(cmd[count]->pipe_fd[1]);
		}
		count++;
	}
}
