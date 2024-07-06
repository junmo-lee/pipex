/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:41:45 by junmlee           #+#    #+#             */
/*   Updated: 2024/07/06 22:05:05 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	f(void)
{
	system("leaks debug.out");
}

int	wait_processes(t_vars *var, t_cmd *cmd[])
{
	int	count;
	int	last_status;

	last_status = 0;
	count = 0;
	while (count < var->argc - 3)
	{
		//while(1);
		if (waitpid(cmd[count]->pid, &(cmd[count]->status), 0) == -1)
			exit(EXIT_FAILURE);
		// for debug
		ft_putnbr_fd(WEXITSTATUS(cmd[count]->status), STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		if (count == var->argc -4)
			last_status = WEXITSTATUS(cmd[var->argc - 4]->status);
		free_cmds(cmd[count]);
		count++;
	}
	return (last_status);
}


int	main(int argc, char *argv[], char *envp[])
{
	t_vars	vars;
	t_cmd	*cmd[100];

	atexit(f);
	init(&vars, argc, argv, envp);
	if (argc != 5)
	{
		free_strs(vars.path);
		return (EXIT_FAILURE);
	}
	read_file(&(vars.file1_read_fd), argv[1]);
	write_file(&(vars.file2_write_fd), argv[4]);

	do_pipex(&vars, cmd);
	close(vars.file1_read_fd);
	close(vars.file2_write_fd);
	// for(int i=0;vars.path[i]!=NULL;i++)
	// {
	// 	ft_putstr_fd(vars.path[i], STDERR_FILENO);
	// 	ft_putchar_fd('\n', STDERR_FILENO);
	// }
	free_strs(vars.path);
	return (wait_processes(&vars, cmd));
}
