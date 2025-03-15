/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalaibb <msalaibb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:06:39 by msalaibb          #+#    #+#             */
/*   Updated: 2025/03/15 14:50:50 by msalaibb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	see_free(char *str)
{
	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
}

void	free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i] != NULL)
		free(split[i]);
	free(split);
}

void	free_all(char *str, int error_num)
{
	t_cmds	*cmds;
	t_cmds	*cmds_copy;
	t_flags	*flags_copy;
	t_flags	*flags;

	close_all(get_t_min()->in_fd, get_t_min()->out_fd);
	cmds = get_t_min()->cmds;
	while (cmds != NULL)
	{
		cmds_copy = cmds->next;
		see_free(cmds->path);
		see_free(cmds->cmd);
		flags = cmds->flags;
		while (flags != NULL)
		{
			flags_copy = flags->next;
			see_free(flags->flag);
			free(flags);
			flags = flags_copy;
		}
		free(cmds);
		cmds = cmds_copy;
	}
	if (error_num != -1)
		exit_error_minishell(str, error_num);
}

void	exit_error_minishell(char *str, int error_num)
{
	ft_putstr_fd(str, 2);
	exit(error_num);
}
