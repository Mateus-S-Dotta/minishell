/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:49:37 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/29 18:12:35 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_strisonly(const char *str, char c)
{
	while (*str)
	{
		if (*str != c)
			return (0);
		str++;
	}
	return (1);
}

int	ft_echo(t_cmds *cmd)
{
	int		flag_n;
	t_flags	*flag_ptr;

	flag_n = 0;
	flag_ptr = cmd->flags;
	while (flag_ptr && flag_ptr->flag
		&& ft_strncmp(flag_ptr->flag, "-n", 2) == 0
		&& ft_strisonly(flag_ptr->flag + 1, 'n'))
	{
		flag_n = 1;
		flag_ptr = flag_ptr->next;
	}
	while (flag_ptr)
	{
		if (flag_ptr->flag && *(flag_ptr->flag))
		{
			ft_putstr_fd(flag_ptr->flag, 1);
			if (flag_ptr->next)
				write(1, " ", 1);
		}
		flag_ptr = flag_ptr->next;
	}
	if (!flag_n)
		write(1, "\n", 1);
	return (0);
}
