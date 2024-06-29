#include "pipex.h"
#include <stdio.h>

int	parse_name_args(t_cmd *cmd, char *full_cmd);

void	f()
{
	system("leaks debug.out");
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

//execve(vars.cmd1->cmd_path, vars.cmd1->args, vars.cmd1->envp);
int warp_cmd_execve(t_cmd *cmd)
{
	return (execve(cmd->cmd_path, cmd->args, cmd->envp));
}

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
			// 앞부분 path= 지우기
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

int	init(t_vars *vars, int argc, char *argv[], char *envp[])
{
	char	*temp;

	ft_memset(vars, 0, sizeof(vars));
	vars->argc = argc;
	vars->argv = argv;
	vars->envp = envp;
	import_path(vars);
	return (0);
}



int	main(int argc, char *argv[], char *envp[])
{
	t_vars	vars;

	atexit(f);
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
	vars.file1_fd[0] = open(argv[1], O_RDONLY);
	//warp_cmd_execve(vars.cmd1);
	warp_cmd_execve(vars.cmd2);
	// vars.cmd1 = fork();
	// vars.cmd2 = fork();
	// vars.cmd1_fd[0] = dup(vars.file1_fd[0]);
	exit(EXIT_SUCCESS);
}
