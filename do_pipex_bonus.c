/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipex_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:57:08 by junmlee           #+#    #+#             */
/*   Updated: 2024/07/20 20:51:57 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	child(t_vars *vars, t_cmd *cmd)
{
	if (dup2(vars->prev_read, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(vars->prev_read);
	if (dup2(vars->next_write, STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(vars->next_write);
	close(vars->pipe_fd[0]);
	if (access(cmd->cmd_name, X_OK) == 0)
		cmd->cmd_path = cmd->cmd_name;
	else
		check_cmd_access(vars, cmd);
	if (execve(cmd->cmd_path, cmd->args, cmd->envp) == -1)
		exit(EXIT_FAILURE);
}

void	do_pipex_bonus(t_vars *vars, t_cmd *cmd[])
{
	int		count;
	pid_t	fork_ret;

	vars->prev_read = dup(vars->file1_read_fd);
	count = 0;
	while (count < vars->cmd_len)
	{
		cmd[count] = cmd_init(vars, vars->argv[count + 2 + vars->is_here_doc]);
		if (count != vars->cmd_len - 1)
		{
			if (pipe(vars->pipe_fd) == -1)
				exit(EXIT_FAILURE);
			vars->next_write = dup(vars->pipe_fd[1]);
			close(vars->pipe_fd[1]);
		}
		else
			vars->next_write = dup(vars->file2_write_fd);
		fork_ret = fork();
		if (fork_ret == -1)
			exit(EXIT_FAILURE);
		else if (fork_ret == 0)
			child(vars, cmd[count]);
		else
		{
			cmd[count]->pid = fork_ret;
			if (count != vars->cmd_len - 1)
			{
				close(vars->prev_read);
				close(vars->next_write);
				vars->prev_read = dup(vars->pipe_fd[0]);
				close(vars->pipe_fd[0]);
			}
		}
		count++;
	}
}
