/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 10:07:20 by msalaibb          #+#    #+#             */
/*   Updated: 2025/04/29 16:24:10 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	complete_array(t_cmds *cmds, char **new_cmds)
{
	t_flags	*flags_copy;
	int		i;

	i = 0;
	if (cmds->cmd != NULL)
		new_cmds[i++] = cmds->cmd;
	flags_copy = cmds->flags;
	while (flags_copy != NULL)
	{
		if (flags_copy->flag != NULL)
			new_cmds[i++] = flags_copy->flag;
		flags_copy = flags_copy->next;
	}
	if (!is_builtins(cmds->cmd, 7))
		cmds->path = find_paths(new_cmds[0]);
}

char	**unify_flags(t_cmds *cmds)
{
	char	**new_cmds;
	int		i;
	t_flags	*flags_copy;

	i = 0;
	if (cmds->cmd != NULL)
		i += 1;
	flags_copy = cmds->flags;
	while (flags_copy != NULL)
	{
		if (flags_copy->flag != NULL)
			i += 1;
		flags_copy = flags_copy->next;
	}
	if (i == 0)
		free_all("", 1);
	new_cmds = (char **)ft_calloc(i + 1, sizeof(char *));
	if (new_cmds == NULL)
		free_all("Malloc Error\n", 1);
	complete_array(cmds, new_cmds);
	return (new_cmds);
}

void	close_all(int fd_1, int fd_2)
{
	close(fd_1);
	close(fd_2);
}

void	super_close(int fd_1, int fd_2, int redirect, int qnt_hd)
{
	while (qnt_hd > 0)
	{
		wait(NULL);
		qnt_hd--;
	}
	if (dup2(fd_1, redirect) == -1)
		exit_error_minishell("Dup2 Error\n", 1);
	close_all(fd_1, fd_2);
}

int	new_flag(t_cmds *new_cmds, char *cmd, int type)
{
	t_flags	*new_flag;
	t_flags	*temp;

	new_flag = (t_flags *)malloc(sizeof(t_flags));
	if (new_flag == NULL)
		return (free_normal_comand(new_cmds, NULL), 0);
	new_flag->next = NULL;
	new_flag->flag = ft_strdup(cmd);
	if (new_flag->flag == NULL)
		return (free(new_flag), free_normal_comand(new_cmds, NULL), 0);
	new_flag->quote = type;
	if (new_cmds->flags == NULL)
		new_cmds->flags = new_flag;
	else
	{
		temp = new_cmds->flags;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_flag;
	}
	return (1);
}
