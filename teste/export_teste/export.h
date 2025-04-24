/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 01:27:33 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/23 20:56:27 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_H
# define EXPORT_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "gnl/get_next_line.h"

#define FILE_NAME "env_tmp"

void	print_in_order(char **env);
char	**copy_env(char **env);
char	*ft_strdup(const char *s);
char	**ft_split(char const *s, char c);
int		open_file(char *file_name, int type);
void	free_splited(char **splited);
int		cnt_env(void);
void	add_or_update_env(char **values, char **env, char *input);
char	**update_env(char **env);
void	write_in_file(int fd_f, char **env);


#endif /* EXPORT_H */