/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:53:05 by junmlee           #+#    #+#             */
/*   Updated: 2024/07/10 17:10:39 by junmlee          ###   ########.fr       */
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
	while (count < var->cmd_len)
	{
		if (waitpid(cmd[count]->pid, &(cmd[count]->status), 0) == -1)
			return (EXIT_FAILURE);
		if (count == var->cmd_len - 1)
			last_status = get_exit_status(cmd[count]->status);
		free_cmds(cmd[count]);
		count++;
	}
	close(var->file1_read_fd);
	close(var->file2_write_fd);
	if (var->is_here_doc == 1)
		unlink(".here_doc");
	free_strs(var->path, EXIT_SUCCESS);
	return (last_status);
}

void	bonus_get_fds(t_vars *vars)
{
	if (ft_strncmp(vars->argv[1], "here_doc", ft_strlen(vars->argv[1])) == 0)
	{
		vars->is_here_doc = 1;
		write_here_doc(vars);
		read_file(&(vars->file1_read_fd), ".here_doc", O_RDONLY);
		write_file(&(vars->file2_write_fd), vars->argv[vars->argc - 1], \
			O_WRONLY | O_CREAT | O_APPEND);
	}
	else
	{
		vars->is_here_doc = 0;
		read_file(&(vars->file1_read_fd), vars->argv[1], O_RDONLY);
		write_file(&(vars->file2_write_fd), vars->argv[vars->argc - 1], \
			O_WRONLY | O_CREAT | O_TRUNC);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_vars	vars;
	t_cmd	*cmd[OPEN_MAX];

	init(&vars, argc, argv, envp);
	if (argc < 5)
		exit(free_strs(vars.path, EXIT_FAILURE));
	bonus_get_fds(&vars);
	if (vars.is_here_doc == 1)
		vars.cmd_len = argc - 4;
	else
		vars.cmd_len = argc - 3;
	do_pipex_bouns(&vars, cmd);
	return (wait_processes(&vars, cmd));
}
