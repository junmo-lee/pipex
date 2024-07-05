/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:24:23 by junmlee           #+#    #+#             */
/*   Updated: 2024/07/05 19:05:54 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include "ft_printf/ft_printf.h"
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>

typedef struct s_cmd
{
	pid_t	pid;
	char	*cmd_path; // 필요함
	char	**args; // 필요함
	char	**envp; // 필요x
	char	*cmd_name; // 필요
	int		pipe_fd[2];
	int		cant_execute;
	int		status;
}	t_cmd;

typedef struct s_vars
{
	int				argc;
	char			**argv;
	char			**envp;
	char			**path; // 내가 malloc한거, free 해줘야함
	int				file1_read_fd;
	int				file2_write_fd;
}	t_vars;

char	*path_join(char const *s1, char const *s2);
int		init(t_vars *vars, int argc, char *argv[], char *envp[]);
t_cmd	*cmd_init(t_vars *vars, char *cmd_argv);
int		warp_cmd_execve(t_cmd *cmd);
void	do_pipex(t_vars *vars, t_cmd *cmd[]);
void	check_cmd_access(t_vars *vars, t_cmd *cmd);

int		write_stderr(char *error_msg, char *name);
int		write_stderr_exit(char *error_msg, char *name, int errorcode);

int		read_file(int *fd, char *file_path);
int		write_file(int *fd, char *file_path);
void	free_strs(char *strs[]);
void	free_cmds(t_cmd *cmd);

#endif