/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:53:05 by junmlee           #+#    #+#             */
/*   Updated: 2024/07/23 15:13:08 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_exit_status(int status)
{
	return (((*(int *)&(status)) >> 8) & 0x000000ff);
}

void	wait_processes(t_vars *vars, t_cmd *cmd)
{
	int	count;
	int	exit_count;
	int	ret;

	exit_count = 0;
	while (exit_count < vars->cmd_len)
	{
		count = 0;
		while (count < vars->cmd_len)
		{
			ret = 0;
			if ((cmd + count)->is_end != 1)
				ret = waitpid((cmd + count)->pid, \
					&((cmd + count)->status), WNOHANG);
			if (ret == -1)
				exit (EXIT_FAILURE);
			else if (ret != 0)
			{
				(cmd + count)->is_end = 1;
				exit_count++;
				free_cmds((cmd + count));
			}
			count++;
		}
	}
}

int	main_return(t_vars *vars, t_cmd *cmd)
{
	wait_processes(vars, cmd);
	free_strs(vars->path, EXIT_SUCCESS);
	return (get_exit_status((cmd + (vars->cmd_len - 1))->status));
}

int	main(int argc, char *argv[], char *envp[])
{
	t_vars	vars;
	t_cmd	cmd[2];

	init(&vars, argc, argv, envp);
	if (argc != 5)
		exit(free_strs(vars.path, EXIT_FAILURE));
	read_file(&vars.file1_read_fd, vars.argv[1], O_RDONLY);
	write_file(&vars.file2_write_fd, vars.argv[vars.argc - 1], \
		O_WRONLY | O_CREAT | O_TRUNC);
	vars.cmd_len = argc - 3;
	do_pipex(&vars, cmd);
	return (main_return(&vars, cmd));
}
