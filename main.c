/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:41:45 by junmlee           #+#    #+#             */
/*   Updated: 2024/07/04 18:11:40 by junmlee          ###   ########.fr       */
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
			exit(EXIT_FAILURE);
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
	vars.file1_read_fd = open(argv[1], O_RDONLY);
	vars.file2_write_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (vars.file1_read_fd == -1 || vars.file2_write_fd == -1)
		return (EXIT_FAILURE);
	do_pipex(&vars, cmd);
	return (wait_processes(&vars, cmd));
}
