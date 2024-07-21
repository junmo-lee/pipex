/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:53:05 by junmlee           #+#    #+#             */
/*   Updated: 2024/07/21 17:36:41 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	get_exit_status(int status)
{
	return (((*(int *)&(status)) >> 8) & 0x000000ff);
}

void	wait_processes(t_vars *vars, t_cmd *cmd[])
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
			if (cmd[count]->is_end != 1)
				ret = waitpid(cmd[count]->pid, &(cmd[count]->status), WNOHANG);
			if (ret == -1)
				exit (EXIT_FAILURE);
			else if (ret != 0)
			{
				cmd[count]->is_end = 1;
				exit_count++;
				free_cmds(cmd[count]);
			}
			count++;
		}
	}
}

int	main_return(t_vars *vars, t_cmd *cmd[])
{
	wait_processes(vars, cmd);
	if (vars->is_here_doc == 1)
		unlink(".here_doc");
	free_strs(vars->path, EXIT_SUCCESS);
	return (get_exit_status(cmd[vars->cmd_len - 1]->status));
}

void	bonus_get_fds(t_vars *vars)
{
	if (ft_strncmp(vars->argv[1], "here_doc", ft_strlen(vars->argv[1])) == 0 \
		&& ft_strlen(vars->argv[1]) == ft_strlen("here_doc"))
	{
		vars->is_here_doc = 1;
		unlink(".here_doc");
		write_file(&(vars->here_doc_fd), ".here_doc", \
			O_WRONLY | O_CREAT | O_TRUNC);
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
	vars.cmd_len = argc - 3 - vars.is_here_doc;
	do_pipex_bonus(&vars, cmd);
	return (main_return(&vars, cmd));
}
