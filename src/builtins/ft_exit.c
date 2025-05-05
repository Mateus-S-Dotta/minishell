/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:57:20 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/05/05 16:18:00 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_num(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_cmds *cmds, int *fd)
{
	int		exit_code;

	exit_code = 0;
	ft_putstr_fd("exit\n", 1);
	if (!cmds->flags)
	{
		close_all(fd[0], fd[1]);
		free_all(NULL, 0);
	}
	if (!is_num(cmds->flags->flag))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmds->flags->flag, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (2);
	}
	if (cmds->flags->next)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd("too many arguments\n", 2);
		return (1);
	}
	exit_code = (ft_atoi(cmds->flags->flag) % 256 + 256) % 256;
	close_all(fd[0], fd[1]);
	free_all(NULL, exit_code);
	return (0);
}
