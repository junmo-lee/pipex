#include "pipex.h"
#include <stdio.h>

void	f()
{
	system("leaks debug.out");
}

int	I_WIFEXITED(int status)
{
	return (!(status & 0x0F));
}

int	I_WEXITSTATUS(int status)
{
	return (status >> 8);
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

void	do_pipex(t_vars *vars)
{
	pid_t	pid;
	
	
	pid = fork();
	
	if (pid == -1)
		return ;
	else if (pid == 0)
	{
		//cmd2 공간
		//cmd2는 cmd1 에서 파이프를 통해 넘어온 pipe_fd[0] 로 읽고
		//file2_write_fd 로 써야함
		close(vars->pipe_fd[1]); // cmd2는 파이프로 쓸 필요가 없다

		dup2(vars->pipe_fd[0], STDIN_FILENO);
		dup2(vars->file2_write_fd, STDOUT_FILENO);
		warp_cmd_execve(vars->cmd2);
	}
	else
	{	
		ft_printf("parent!\n"); // 문제없이 stdout에 
		
		//cmd1 공간
		//cmd1은 file1_read_fd 로 읽고
		//pipe_fd[1] 로 cmd2 로 넘겨줘야함
		close(vars->pipe_fd[0]); //cmd1은 파이프로 읽을 필요가 없음


		//shell command는 표준 입력으로 읽고, 표준 출력으로 쓰기 때문에
		dup2(vars->file1_read_fd, STDIN_FILENO); // 표준 입력을 파일1번 읽기로 변경하고
		dup2(vars->pipe_fd[1], STDOUT_FILENO); // 표준 출력을 파이프로 넘겨준다
		//dup2에서 바꾸면서 기존 표준 입출력을 닫아줌

		warp_cmd_execve(vars->cmd1); // cmd1 을 실행

		// vars->main_pid = pid;
		//int	child1_status;
		// int	check_child1_pid = waitpid(vars->cmd1->pid, &child1_status, WNOHANG);
		// if (check_child1_pid != vars->cmd1->pid)
		// 	ft_printf("error!\n");
	}


	// vars.cmd1 = fork();
	// vars.cmd2 = fork();
	// vars.cmd1_fd[0] = dup(vars.file1_fd[0]);
	// waitpid(vars->cmd2->pid, 0, 0);
	wait(NULL);
	//exit(EXIT_SUCCESS);
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

	pipe(vars.pipe_fd);
	vars.file1_read_fd = open(argv[1], O_RDONLY);
	vars.file2_write_fd = open(argv[4], O_WRONLY);
	do_pipex(&vars);
	wait(NULL);
	//wait(NULL);
}
