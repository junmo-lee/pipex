/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:41:45 by junmlee           #+#    #+#             */
/*   Updated: 2024/07/03 22:49:59 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int warp_cmd_execve(t_cmd *cmd)
{
	// ft_printf("cmd_path : %s\n", cmd->cmd_path);
	// ft_printf("args : \n");
	// for(int i=0;cmd->args[i] != NULL;i++)
	// 	ft_printf("%s\n", cmd->args[i]);
	// ft_printf("envp : \n");
	// for(int i=0;cmd->envp[i] != NULL;i++)
	// 	ft_printf("%s\n", cmd->envp[i]);
	return (execve(cmd->cmd_path, cmd->args, cmd->envp));
}

void wait_processes(t_cmd *cmd[])
{
	int i;
	int status;
	int count;
	pid_t	wait_ret;

	count = 0;
	while (count < 2)
	{
		i = 0;
		while (i < 2)
		{
//			wait(&status);
			wait_ret = waitpid(cmd[i]->pid, &status, WNOHANG);
			if (wait_ret == -1)
				exit(EXIT_FAILURE);
			else if (wait_ret != 0)
			count++;
			i++;
		}
	}
}

// void	do_pipex(t_vars *vars, pid_t *pids)
// {
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid == -1)
// 		return ;
// 	else if (pid == 0)
// 	{
// 		pid = fork();
// 		if (pid == -1)
// 			return ;
// 		else if (pid == 0)
// 		{
// 			close(vars->pipe_fd[1]);
// 			dup2(vars->pipe_fd[0], STDIN_FILENO);
// 			dup2(vars->file2_write_fd, STDOUT_FILENO);
// 			warp_cmd_execve(vars->cmd2);
// 		}
// 		else
// 		{
// 			//cmd1
// 			vars->cmd2->pid = pid;
// 			pids[1] = pid;
// 			close(vars->pipe_fd[0]);
// 			dup2(vars->file1_read_fd, STDIN_FILENO);
// 			dup2(vars->pipe_fd[1], STDOUT_FILENO);
// 			warp_cmd_execve(vars->cmd1);
// 		}
// 	}
// 	else
// 	{
// 		//main 함수
// 		vars->cmd1->pid = pid;
// 		pids[0] = pid;
// 	}
// }

int	main(int argc, char *argv[], char *envp[])
{
	t_vars	vars;
	int		count;
	pid_t	fork_ret;
	t_cmd 	*cmd[100];

	init(&vars, argc, argv, envp);
	if (argc != 5)
		return (EXIT_FAILURE);
	count = 0;
	while (count < vars.argc - 3)
	{
		cmd[count] = cmd_init(&vars, argv[count + 2]);
		count++;
	}
	// vars.cmd1 = cmd_init(&vars, argv[2]);
	// vars.cmd2 = cmd_init(&vars, argv[3]);

	vars.file1_read_fd = open(argv[1], O_RDONLY);
	vars.file2_write_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (vars.file1_read_fd == -1 || vars.file2_write_fd == -1)
		return (EXIT_FAILURE);
	
	count = 0;
	while (count < vars.argc - 3)
	{
		pipe(cmd[count]->pipe_fd);
		fork_ret = fork();
		if (fork_ret == -1)
			exit(EXIT_FAILURE);
		else if (fork_ret == 0)
		{
			// close(cmd[count]->pipe_fd[0]);
			if (count == 0)
				dup2(vars.file1_read_fd, STDIN_FILENO);
			else
				dup2(cmd[count - 1]->pipe_fd[0], STDIN_FILENO);
				//dup2(cmd[count]->pipe_fd[0], cmd[count - 1]->pipe_fd[0]);
			if (count != 1)
				dup2(cmd[count]->pipe_fd[1], STDOUT_FILENO);
			else
				dup2(vars.file2_write_fd, STDOUT_FILENO);
			warp_cmd_execve(cmd[count]);
		}
		else
		{
			// if (count != 0)
			// {
			// 	close(cmd[count]->pipe_fd[1]);
			// 	dup2(cmd[count]->pipe_fd[0], STDIN_FILENO);
			// 	if (count == vars.argc - 4)
			// 		dup2(cmd[count]->pipe_fd[1], vars.file2_write_fd);
			// }
			cmd[count]->pid = fork_ret;
			// waitpid(fork_ret, NULL, 0);
		}
		count++;
	}
	int status;

	if(wait(&status) == -1)
		ft_putnbr_fd(42, STDERR_FILENO);
	// if(wait(&status) == -1)
	// 	ft_putnbr_fd(42, STDERR_FILENO);
	// wait_processes(cmd);
}
