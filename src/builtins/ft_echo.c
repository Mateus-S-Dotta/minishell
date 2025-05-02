/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:49:37 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/29 20:34:02 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int ft_strisonly(const char *str, char c)
{
	while (*str)
	{
		if (*str != c)
			return (0);
		str++;
	}
	return (1);
}

static t_flags	*process_flags(t_cmds *cmd, int *flag_n)
{
	t_flags	*flag_ptr;

	*flag_n = 0;
	flag_ptr = cmd->flags;
	while (flag_ptr && flag_ptr->flag
		   && ft_strncmp(flag_ptr->flag, "-n", 2) == 0
		   && ft_strisonly(flag_ptr->flag + 1, 'n'))
	{
		*flag_n = 1;
		flag_ptr = flag_ptr->next;
	}
	return (flag_ptr);
}

static t_flags	*find_last_valid_flag(t_flags *flags)
{
	t_flags		*current;
	t_flags		*last_valid;

	current = flags;
	last_valid = NULL;
	while (current)
	{
		if (current->flag && *(current->flag))
			last_valid = current;
		current = current->next;
	}
	return (last_valid);
}

int	ft_echo(t_cmds *cmd)
{
	int		flag_n;
	t_flags	*flag_ptr;
	t_flags	*last_valid;

	flag_ptr = process_flags(cmd, &flag_n);
	last_valid = find_last_valid_flag(cmd->flags);
	while (flag_ptr)
	{
		if (flag_ptr->flag && *(flag_ptr->flag))
		{
			ft_putstr_fd(flag_ptr->flag, 1);
			if (flag_ptr != last_valid)
				write(1, " ", 1);
		}
		flag_ptr = flag_ptr->next;
	}
	if (!flag_n)
		write(1, "\n", 1);
	return (0);
}