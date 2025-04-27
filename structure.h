/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:23:24 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/27 17:24:27 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

#include "minishell.h"

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
	int		sig;
	char	**env;
	char	*src_pwd;
	int		pipe_cnt;
	int		error;
	pid_t	prc_pid[1024];
	t_cmds	*cmds;
}	t_min;

#endif