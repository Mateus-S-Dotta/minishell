/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 01:27:33 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/23 02:33:30 by lsilva-x         ###   ########.fr       */
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

#endif /* EXPORT_H */