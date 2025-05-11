/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:23:24 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/05/11 00:08:41 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

# include "minishell.h"

typedef struct s_flags
{
	char			*flag;
	int				quote;
	int				redirect;
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

typedef struct s_min
{
	int		in_fd;
	int		out_fd;
	int		sig;
	char	**env;
	int		pipe_cnt;
	int		*pipe_ptr;
	int		error;
	pid_t	prc_pid[1024];
	t_cmds	*cmds;
}	t_min;

typedef struct gc_block
{
	void				*ptr;
	unsigned long		size;
	char				*tag;
	struct gc_block		*next;
}	t_gc_block;

typedef struct gc_state
{
	t_gc_block		*allocations;
	unsigned long	total_size;
	unsigned long	num_allocations;
}	t_gc_state;

#endif