/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:49:37 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/16 16:52:51 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static char	*unify_str(t_flags *flag)
// {
// 	char	*str;
// 	char	*tmp;

// 	str = NULL;
// 	while (flag)
// 	{
// 		tmp = str;
// 		str = ft_strjoin(str, flag->flag);
// 		if (!str)
// 		{
// 			free(tmp);
// 			return (NULL);
// 		}
// 		free(tmp);
// 		flag = flag->next;
// 	}
// 	return (str);
// }

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

// static int	cnt_arg(char **s_tr)
// {
// 	int		i;
// 	i = -1;
// 	while (s_str[++i])
// 		(void);
// 	return (i);
// }

// int	ft_echo(char **args)
// {
// 	int		flag_break;
// 	int		i;

// 	flag_break = 0;
// 	i = 0;
// 	if (cmd->next)
// 		cmd = cmd->next; // Move to the next command
// 	if (cmd && cmd->cmd)
// 	{
// 		if (cmd->flags && ft_strncmp(cmd->flags->flag, "-n", 2) == 0)
// 			flag_break = 1;
// 		while (cmd->cmd[i])
// 		{
// 			ft_putstr_fd(&cmd->cmd[i], 1);
// 			if (cmd->cmd[i + 1] && cmd->cmd[i] != '\0')
// 				write(1, " ", 1);
// 			i++;
// 		}
// 	}
// 	if (!flag_break)
// 		write(1, "\n", 1);
// 	return (EXIT_SUCCESS);
// }