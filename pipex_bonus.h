/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:56:28 by junmlee           #+#    #+#             */
/*   Updated: 2024/07/20 22:02:26 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft/libft.h"
# include "gnl/get_next_line.h"

# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <limits.h>

typedef struct s_cmd
{
	pid_t	pid;
	char	*cmd_path;
	char	*cmd_name;
	char	**args;
	char	**envp;
	int		cant_execute;
	int		status;
	int		is_end;
}	t_cmd;

typedef struct s_vars
{
	int				argc;
	char			**argv;
	char			**envp;
	char			**path;
	int				file1_read_fd;
	int				file2_write_fd;
	int				here_doc_fd;
	int				pipe_fd[2];
	int				prev_read;
	int				next_write;
	int				cmd_len;
	int				is_here_doc;
}	t_vars;

char	*path_join(char const *s1, char const *s2);
void	init(t_vars *vars, int argc, char *argv[], char *envp[]);
t_cmd	*cmd_init(t_vars *vars, char *cmd_argv);

void	do_pipex_bonus(t_vars *vars, t_cmd *cmd[]);
void	check_cmd_access(t_vars *vars, t_cmd *cmd);

int		write_stderr(char *error_msg, char *name);
void	write_stderr_exit(char *error_msg, char *name, int errorcode);
char	**pipex_split(char *str, char c);

void	read_file(int *fd, char *file_path, int option);

void	write_file(int *fd, char *file_path, int option);
void	write_here_doc(t_vars *vars);

int		free_strs(char *strs[], int exit_code);
void	free_cmds(t_cmd *cmd);
int 	check_fd(void);
#endif