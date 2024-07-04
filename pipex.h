/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:24:23 by junmlee           #+#    #+#             */
/*   Updated: 2024/07/04 18:34:46 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>

typedef struct s_cmd
{
	pid_t	pid;
	char	*cmd_path;
	char	**args;
	char	**envp;
	char	*cmd_name;
	int		pipe_fd[2];
	int		status;
}	t_cmd;

typedef struct s_vars
{
	int				argc;
	char			**argv;
	char			**envp;
	char			**path;
	int				file1_read_fd;
	int				file2_write_fd;
}	t_vars;

char	*path_join(char const *s1, char const *s2);
int		init(t_vars *vars, int argc, char *argv[], char *envp[]);
t_cmd	*cmd_init(t_vars *vars, char *cmd_argv);
int		warp_cmd_execve(t_cmd *cmd);
void	do_pipex(t_vars *vars, t_cmd *cmd[]);
int		check_cmd_access(t_vars *vars, t_cmd *cmd);

#endif