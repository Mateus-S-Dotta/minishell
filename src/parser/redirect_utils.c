/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 15:42:23 by msalaibb          #+#    #+#             */
/*   Updated: 2025/05/09 02:57:10 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_more(t_cmds *cmds, int *controller)
{
	t_flags	*flags_copy;
	t_flags	*flags_next;

	flags_copy = cmds->flags;
	while (flags_copy != NULL)
	{
		if (flags_copy->quote == 0 && flags_copy->flag
			&& (flags_copy->flag[0] == '>' || flags_copy->flag[0] == '<'))
		{
			flags_copy->redirect = 1;
			flags_next = flags_copy->next;
			controller[if_redirect(flags_copy, flags_next)] = 1;
			flags_copy = cmds->flags;
		}
		flags_copy = flags_copy->next;
	}
}

void	free_cmd(t_cmds *f1)
{
	free(f1->cmd);
	f1->cmd = NULL;
}

void	free_flag(t_flags *f1)
{
	free(f1->flag);
	f1->flag = NULL;
}

int	confitions_redirect(t_flags *f1, int situation)
{
	if (situation == 0)
	{
		if (f1->flag[0] == '>' && f1->flag[1] == '>' && f1->flag[2] == '\0')
			return (1);
		return (0);
	}
	else
	{
		if (f1->flag[0] == '>' && f1->flag[1] == '>' && f1->flag[2] != '\0')
			return (1);
		return (0);
	}
}
