/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:41:45 by junmlee           #+#    #+#             */
/*   Updated: 2024/07/07 16:21:23 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_exit_status(int status)
{
	return (((*(int *)&(status)) >> 8) & 0x000000ff);
}

int	wait_processes(t_vars *var, t_cmd *cmd[])
{
	int	count;
	int	last_status;

	last_status = 0;
	count = 0;
	while (count < var->argc - 3)
	{
		if (waitpid(cmd[count]->pid, &(cmd[count]->status), 0) == -1)
			return (EXIT_FAILURE);
		ft_putnbr_fd(WEXITSTATUS(cmd[count]->status), STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		if (count == var->argc -4)
			last_status = get_exit_status(cmd[var->argc - 4]->status);
		free_cmds(cmd[count]);
		count++;
	}
	return (last_status);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_vars	vars;
	t_cmd	*cmd[2];

	init(&vars, argc, argv, envp);
	if (argc != 5)
		exit(free_strs(vars.path, EXIT_FAILURE));
	read_file(&(vars.file1_read_fd), argv[1]);
	write_file(&(vars.file2_write_fd), argv[4]);
	do_pipex(&vars, cmd);
	close(vars.file1_read_fd);
	close(vars.file2_write_fd);
	free_strs(vars.path, EXIT_SUCCESS);
	return (wait_processes(&vars, cmd));
}
