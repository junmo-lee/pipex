#include "pipex.h"
#include <stdio.h>

void	f()
{
	system("leaks debug.out");
}


//execve(vars.cmd1->cmd_path, vars.cmd1->args, vars.cmd1->envp);
int warp_cmd_execve(t_cmd *cmd)
{
	return (execve(cmd->cmd_path, cmd->args, cmd->envp));
}


// cmd_name 과 path를 가지고 access 확인, 해당 경로를 full_path에 넣어줌
int check_cmd_access(t_vars *vars, t_cmd *cmd)
{
	char	*temp;
	int		i;

	i = 0;
	while (vars->path[i] != NULL)
	{
		temp = path_join(vars->path[i], cmd->cmd_name);
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


int	main(int argc, char *argv[], char *envp[])
{
	t_vars	vars;

	//atexit(f);
	init(&vars, argc, argv, envp);
	if (argc != 5)
		return(EXIT_FAILURE);
	if (access(argv[1], R_OK) == 0)
		ft_printf("file 1 can read\n");

	vars.cmd1 = cmd_init(&vars, argv[2]);
	if (check_cmd_access(&vars, vars.cmd1) == 0)
		ft_printf("cmd 1 can excute\n");

	vars.cmd2 = cmd_init(&vars, argv[3]);
	if (check_cmd_access(&vars, vars.cmd2) == 0)
		ft_printf("cmd 2 can excute\n");

	if (access(argv[4], W_OK) == 0)
		ft_printf("file 2 can write\n");

	int	pipe_fd[2];
	pid_t	pid = fork();
	if (pid == -1)
		return (0);
	else if (pid == 0)
	{
		pid = fork();
		if (pid == -1)
			ft_printf("fork fail!\n");
		else if (pid == 0)
		{
			
			ft_printf("child2!\n");
			// vars.file2_fd[1] = open(argv[1], O_WRONLY);
			//file2 쓰는거를 cmd2의 쓰는 방향으로
			vars.cmd2->fd[1] = open(argv[4], O_WRONLY);
			//cmd2 읽는 거를 pipe의 쓰는 방향으로
			dup2(vars.cmd2->fd[0], pipe_fd[1]);
			warp_cmd_execve(vars.cmd2);
		}
		else
		{
			vars.cmd2->pid = pid;
			ft_printf("child1!\n");
			// vars.file1_fd[0] = open(argv[1], O_RDONLY);
			//file1 읽는 거를 cmd1의 읽는 방향으로
			vars.cmd1->fd[0] = open(argv[1], O_RDONLY);
			//cmd1 쓰는 거를 pipe의 읽는 방향으로
			dup2(vars.cmd1->fd[1], pipe_fd[0]);
			//cmd1 실행!
			warp_cmd_execve(vars.cmd1);
		}
	}
	else
	{	
		pipe(pipe_fd);
		ft_printf("parent!\n"); // 문제없이 stdout에 
	}


	// vars.cmd1 = fork();
	// vars.cmd2 = fork();
	// vars.cmd1_fd[0] = dup(vars.file1_fd[0]);
	waitpid(vars.cmd2->pid, 0, 0);
	exit(EXIT_SUCCESS);
}
