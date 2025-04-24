/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:47:33 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/24 16:57:23 by lsilva-x         ###   ########.fr       */
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

int		open_file(char *file_name, int oflag);
int		int_env_file(char **env);
void	write_in_file(int fd_f, char **env);
void	free_splited(char **splited);
int		cnt_env(void);

#endif /* HEADER */