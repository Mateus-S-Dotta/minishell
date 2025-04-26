/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:47:33 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/25 15:38:34 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER
# define HEADER

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "gnl/get_next_line.h"

#define FILE_NAME "env_tmp"

/*INDEX ENV FUNCTIONS */
int		open_file(char *file_name, int oflag);
int		int_env_file(char **env);
void	write_in_file(int fd_f, char **env);
int		cnt_env(void);

/*BUILTINS*/
//export
int		ft_export(char *input, char ***env);
void	print_in_order(char **env);
//env
int		ft_env(char **env);
//unset
int	ft_unset(char *input, char **env);
//cd
int	ft_cd(char *input, char **env);

/*ENV FUNCTIONS */
int		env_searcher(char *field, char **env);
void	env_update(char ***env, char **mng_input, int i);
void	env_delete(char ***env, int i);
int		env_searcher(char *field, char **env);
char	**env_create(char **env, char **mng_input);

/* MANAGEMENT FUNCTIONS */
char	**update_env(char ***env);

/*LIB FUNCTIONS*/
char	*ft_strdup(const char *s);
void	free_splited(char ***splited);
char	**ft_split(char const *s, char c);
char	*ft_strndup(const char *s, size_t n);
int		ft_isalpha(int c);

#endif /* HEADER */