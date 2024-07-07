/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:53:05 by junmlee           #+#    #+#             */
/*   Updated: 2024/07/07 16:22:55 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	wait_processes(t_vars *var, t_cmd *cmd[])
{
	int	count;

	count = 0;
	while (count < var->argc - 3)
	{
		if (waitpid(cmd[count]->pid, &(cmd[count]->status), 0) == -1)
			return (EXIT_FAILURE);
		count++;
	}
	return (WEXITSTATUS(cmd[var->argc - 4]->status));
}

int	main(int argc, char *argv[], char *envp[])
{
	t_vars	vars;
	t_cmd	*cmd[2];

	init(&vars, argc, argv, envp);
	if (argc != 5)
		return (EXIT_FAILURE);
	read_file(&(vars.file1_read_fd), argv[1]);
	write_file(&(vars.file2_write_fd), argv[4]);
	do_pipex(&vars, cmd);
	close(vars.file1_read_fd);
	close(vars.file2_write_fd);
	return (wait_processes(&vars, cmd));
}
