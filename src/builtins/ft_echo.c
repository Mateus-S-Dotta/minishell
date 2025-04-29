/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:49:37 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/28 21:31:03 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_echo(t_cmds *cmd)
{
	int		flag_opt;
	t_flags	*f_tmp;

	flag_opt = 0;
	if (cmd->flags)
	{
		f_tmp = cmd->flags;
		while (ft_strncmp(f_tmp->flag, "-n", 2) == 0)
		{
			flag_opt = 1;
			f_tmp = f_tmp->next;
		}
		while (f_tmp)
		{
			ft_putstr_fd(f_tmp->flag, 1);
			if (f_tmp->next && ft_strncmp(f_tmp->next->flag, "\0", 1) != 0)
				write(1, " ", 1);
			f_tmp = f_tmp->next;
		}
	}
	if (flag_opt == 0)
		write (1, "\n", 1);
	return (0);
}
