/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:49:37 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/27 16:54:47 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_echo(t_cmds *cmd)
{
	int		flag_opt;
	t_flags	*flag_tmp;

	flag_opt = 0;
	if (cmd->flags)
	{
		flag_tmp = cmd->flags;
		while (ft_strncmp(flag_tmp->flag, "-n", 2) == 0)
		{
			flag_opt = 1;
			flag_tmp = flag_tmp->next;
		}
		while (flag_tmp)
		{
			ft_putstr_fd(flag_tmp->flag, 1);
			if (flag_tmp->next && ft_strncmp(flag_tmp->next->flag, "\0", 1) != 0)
				write(1, " ", 1);
			flag_tmp = flag_tmp->next;
		}
	}
	if (flag_opt == 0)
		write (1, "\n", 1);
	return (0);
}
