/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:06:39 by msalaibb          #+#    #+#             */
/*   Updated: 2025/04/27 16:56:54 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
	t_cmds	*cmds_copy;
	t_flags	*flags_copy;
	t_flags	*flags;

	while (get_t_min()->cmds != NULL)
	{
		cmds_copy = get_t_min()->cmds->next;
		see_free(get_t_min()->cmds->path);
		see_free(get_t_min()->cmds->cmd);
		flags = get_t_min()->cmds->flags;
		while (flags != NULL)
		{
			flags_copy = flags->next;
			see_free(flags->flag);
			free(flags);
			flags = flags_copy;
		}
		free(get_t_min()->cmds);
		get_t_min()->cmds = cmds_copy;
	}
	get_t_min()->cmds = NULL;
	if (error_num == -1)
		return ;
	close_all(get_t_min()->in_fd, get_t_min()->out_fd);
	exit_error_minishell(str, error_num);
}

void	exit_error_minishell(char *str, int error_num)
{
	if (get_t_min()->env != NULL)
		free_split(get_t_min()->env);
	ft_putstr_fd(str, 2);
	exit(error_num);
}
