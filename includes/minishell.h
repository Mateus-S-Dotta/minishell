/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:07:17 by msalaibb          #+#    #+#             */
/*   Updated: 2025/05/11 20:26:40 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//Includes
# include "../libft/libft.h"
# include "structure.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <string.h>
# include <dirent.h>
# include <termios.h>
# include <errno.h>
# include <termcap.h>
# include <ttyent.h>

// Define
# define HIS_ER "Historical Error"
# define FILE_NAME "env_tmp"
# define BUFFER_SIZE 50
# define NORMAL_EXIT 1

//Get_next_line.c
char	*get_next_line(int fd);

// Main
t_min	*get_t_min(void);
void	minishell(void);

// Main_utils.c
int		verify_spaces(char *input);
void	new_error(char **cmd);
void	wait_last_status(void);
char	**copy_env(char *env[]);

// Error.c
void	exit_error_minishell(char *str, int error_num);
void	free_split(char **split);
void	free_all(char *str, int error_num);

//Env.c
char	*get_env(char *loo);
char	*find_paths(char *cmd, char **cmds);

//Normal_comand.c
void	normal_comand(char *cmd);
void	create_cmds(t_cmds *cmds, char **cmd_words, int d);
void	free_normal_comand(t_cmds *new_cmds, char **cmd_w);
void	copy_verify(t_cmds *cmds, t_cmds *new_cmds, char **cmd_w, int d);

//Normal_comand_utils.c
int		new_flag(t_cmds *new_cmds, char *cmd, int type);
void	super_close(int fd_1, int fd_2, int redirect, int qnd_hd);
void	close_all(int fd_1, int fd_2);
char	**unify_flags(t_cmds *cmds);

// Redirect.c
void	redirect(int fd, int to_fd, t_cmds *cmds_struct);
int		if_redirect(t_flags *f1, t_flags *f2);

// Redirect_Utils.c
int		confitions_redirect(t_flags *f1, int situation);
void	free_flag(t_flags *f1);
void	free_cmd(t_cmds *f1);
void	handle_more(t_cmds *cmds, int *controller);
int		open_file_r(char *filepath, int flags);

// Unify_.c
int		unify(int i, char **cmd);
int		count_unify(int i, char **cmd, char quote);

// Unify_utils_.c
void	process_char(char current_char, char *quote, int *num, char *new);
char	*init_val(int *num, int i, char **cmd, char quote);
int		max_count(int i, char **cmds);

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
int		*set_heredoc_ptr(int *ptr, int cod);

// Here_doc_utils.c
void	sig_int_hd(int sig);
void	std_hd_sig(void);

// Signal.c
void	set_std_sig(void);
void	std_cmd_c(int sig);
void	std_cmd_back_slash(int sig);
void	set_std_cmd(void);

// Env_file_utils.c
int		int_env_file(char **env);
int		open_file(char *file_name, int oflag);
void	write_in_file(int fd_f, char **env);
char	**update_env(char ***env);
int		cnt_env(void);
char	*env_tmp_relative(void);

// Env_function.c
void	env_update(char ***env, char *mng_input, int i);
void	env_delete(char ***env, int i);
int		env_searcher(char *field, char **env);
char	**env_create(char **env, char *mng_input);
void	free_splited_env(char ***splited);

// Function_utils.c
char	*trim_spaces(char *str);
void	count_pipe(void);

// Builtins_utils.c
int		is_builtins(char *cmd, int range);
void	exec_builtins(t_cmds *cmds, int *fd);

// Ft_echo.c
int		ft_echo(t_cmds *cmd);

// Ft_exit.c
int		ft_exit(t_cmds *cmds, int *fd);

// Ft_pwd.c
int		ft_pwd(void);

// Ft_env.c
int		ft_env(void);

// Ft_cd.c
int		ft_cd(t_cmds *cmds, char ***env);

// Ft_unset.c
int		ft_unset(t_cmds *cmds, char ***env);

// Ft_export.c
int		ft_export(t_cmds *cmds, char ***env);

// Ft_export_utils.c
void	print_in_order(char **env);

#endif