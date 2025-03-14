/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalaibb <msalaibb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:07:17 by msalaibb          #+#    #+#             */
/*   Updated: 2025/03/14 18:07:27 by msalaibb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <readline/readline.h>  // readline
# include <readline/history.h>   // readline history
# include <stdio.h>              // printf, perror, strerror
# include <stdlib.h>             // malloc, free, getenv
# include <unistd.h>             // read, write, fork, execve, access, getcwd, chdir, isatty, ttyname, ttyslot
# include <fcntl.h>              // open
# include <sys/types.h>          // waitpid, wait3, wait4
# include <sys/wait.h>           // wait, waitpid, wait3, wait4
# include <signal.h>             // signal, sigaction, sigemptyset, sigaddset, kill
# include <sys/stat.h>           // stat, lstat, fstat, unlink
# include <sys/ioctl.h>          // ioctl
# include <string.h>             // strerror
# include <dirent.h>             // opendir, readdir, closedir
# include <termios.h>            // tcsetattr, tcgetattr
# include <termcap.h>            // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <ttyent.h>             // ttyslot

// valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --suppressions=supp.supp ./minishell

# define HIS_ER "Historical Error"
# define NORMAL_EXIT 1

typedef struct s_flags
{
	char			*flag;
	int				quote;
	struct s_flags	*next;
}	t_flags;

typedef struct s_cmds
{
	t_flags			*flags;
	char			*path;
	char			*cmd;
	int				quote;
	struct s_cmds	*next;
}	t_cmds;

typedef struct s_min {
	int		in_fd;
	int		out_fd;
	char	**env;
	int		error;

	t_cmds	*cmds;
}	t_min;

// Debug.c
int		debug_fd(void);
void	print_cmds(void);
void	print_split(char **cmds);

// Main
t_min	*get_t_min(void);
void	restart_shell(char *str);

// Main_utils.c
int		verify_spaces(char *input);
void	new_error(char **cmd);

// Error.c
void	exit_error_minishell(char *str, int error_num);
void	free_split(char **split);
void	free_all(char *str, int error_num);

//Env.c
char	*get_env(char *loo);
char	*find_paths(char *cmd);

//Normal_comand.c
void	normal_comand(char *cmd);
void	create_cmds(t_cmds *cmds, char **cmd_words, int d);
void	free_normal_comand(t_cmds *new_cmds, char **cmd_w);

//Normal_comand_utils.c
int		new_flag(t_cmds *new_cmds, char *cmd, int type);
void	super_close(int fd_1, int fd_2, int redirect, int process);
void	close_all(int fd_1, int fd_2);
char	**unify_flags(t_cmds *cmds);

// Redirect.c
void	redirect(int fd, int to_fd, t_cmds *cmds_struct);
int		if_redirect(t_flags *f1, t_flags *f2);

// Redirect_Utils.c
int		confitions_redirect(t_flags *f1, int situation);
void	free_flag(t_flags *f1);
void	free_cmd(t_cmds *f1);
void	handle_more(t_cmds *cmds, char more, int *controller);

// Unify_.c
int		unify(int i, char **cmd);

// Expand.c
void	verify_money_start(char **cmd, int *i, int *in_quote, int *count);
void	verify_money(char **cmd, int *i);

// Super_split.c
char	**super_ft_split(char *cmd);

// Super_split_utils.c
void	copy_str(char *split, char *cmd, int *j);
void	pipe_case(char **split, char *cmd, int *j, int i);

// Super_split_utils_2.c
int		is_word(char *cmd, int i);
void	jump_quotes(char *cmd, int *i, int *count, int find);
void	jump_all(char *cmd, int *i, int *count);
int		count_letter(char *cmd, int j);

// Here_doc.c
int		there_is_heredok(char **cmd, int i);
void	open_here_doc(t_flags *f2);
void	find_all_here_doc(t_cmds *cmd, int *c);

#endif