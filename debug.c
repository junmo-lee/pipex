/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:41:45 by junmlee           #+#    #+#             */
/*   Updated: 2024/07/04 17:30:33 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void wait_processes(t_cmd *cmd[])
{
	// int i;
	int status;
	int count;
	// pid_t	wait_ret;
	cmd++;
	count = 0;
	while (count < 2)
	{
		wait(&status);
		count++;
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
		if (count != vars.argc - 4)
		{
			pipe(cmd[count]->pipe_fd);
			ft_putstr_fd("open pipe ",STDERR_FILENO);
			ft_putnbr_fd(cmd[count]->pipe_fd[0], STDERR_FILENO);
			ft_putstr_fd(":",STDERR_FILENO);
			ft_putnbr_fd(cmd[count]->pipe_fd[1], STDERR_FILENO);
			ft_putstr_fd("\n",STDERR_FILENO);
		}
		fork_ret = fork();
		if (fork_ret == -1)
			exit(EXIT_FAILURE);
		else if (fork_ret == 0)
		{
			//STDIN
			ft_putstr_fd("cmd",STDERR_FILENO);
			ft_putnbr_fd(count,STDERR_FILENO);
			ft_putstr_fd(" ",STDERR_FILENO);
			if (count == 0)
			{
				ft_putnbr_fd(vars.file1_read_fd, STDERR_FILENO);
				dup2(vars.file1_read_fd, STDIN_FILENO);
			}
			else
			{
				ft_putnbr_fd(cmd[count - 1]->pipe_fd[0], STDERR_FILENO);	
				dup2(cmd[count - 1]->pipe_fd[0], STDIN_FILENO);
			}
			ft_putstr_fd("->",STDERR_FILENO);

			//STDOUT
			if (count != vars.argc - 4)
			{
				ft_putnbr_fd(cmd[count]->pipe_fd[1], STDERR_FILENO);
				// 다음 프로세스로 넘어가게 파이프의 입력으로
				dup2(cmd[count]->pipe_fd[1], STDOUT_FILENO);
			}
			else
			{
				ft_putnbr_fd(vars.file2_write_fd, STDERR_FILENO);
				// 마지막 프로세스
				dup2(vars.file2_write_fd, STDOUT_FILENO);
			}

			//자식 프로세스에서의 close
			if (count != vars.argc - 4)
			{
				// count 번째 자식은 count번째 파이프의 읽는 쪽으로 출력을 넘김
				// 따라서 쓰는 쪽의 출력은 필요없음!
				close(cmd[count]->pipe_fd[0]);
			}
			ft_putstr_fd("\n",STDERR_FILENO);
			warp_cmd_execve(cmd[count]);
		}
		else
		{
			//main 프로세스

			//일단 pid 저장시켜주고
			cmd[count]->pid = fork_ret;

			// main 프로세스는 count 번째 프로세스가 만들어졌을때
			// count + 1 프로세스가 필요한 fd 이외에 모두 닫은다음
			// count + 1 프로세스에게 넘겨줘야함!

			if (count != 0)
			{
				close(cmd[count - 1]->pipe_fd[0]);
			}

			if (count != vars.argc - 4)
			{
				close(cmd[count]->pipe_fd[1]);
			}
			// waitpid(fork_ret, NULL, 0);
		}
		count++;
	}

	// if(wait(&status) == -1)
	// 	ft_putnbr_fd(42, STDERR_FILENO);
	wait_processes(cmd);
}
