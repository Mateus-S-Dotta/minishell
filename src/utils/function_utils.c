/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:15:23 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/05/09 01:08:48 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*trim_spaces(char *str)
{
	int		i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	return (&str[i]);
}

void	count_pipe(void)
{
	int		cnt_pipe;
	t_cmds	*cmd_tmp;

	cnt_pipe = 1;
	cmd_tmp = get_t_min()->cmds;
	while (cmd_tmp->next)
	{
		if (cmd_tmp)
			cnt_pipe++;
		cmd_tmp = cmd_tmp->next;
	}
	get_t_min()->pipe_cnt = cnt_pipe;
}
