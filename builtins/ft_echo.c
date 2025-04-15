/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:49:37 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/15 16:02:56 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static int	cnt_arg(**s_tr)
// {
// 	int		i;

// 	i = -1;
// 	while (s_str[++i])
// 		(void);
// 	return (i);
// }

int	ft_echo(t_cmds *cmd)
{
	int		flag_break;
	int		i;

	printf("bbb\n");
	flag_break = 0;
	i = 0;
	if (cmd->next)
		cmd = cmd->next; // Move to the next command
	if (cmd && cmd->cmd)
	{
		if (cmd->flags && ft_strncmp(cmd->flags->flag, "-n", 2) == 0)
			flag_break = 1;
		while (cmd->cmd[i])
		{
			ft_putstr_fd(&cmd->cmd[i], 1);
			if (cmd->cmd[i + 1] && cmd->cmd[i] != '\0')
				write(1, " ", 1);
			i++;
		}
	}
	if (!flag_break)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
