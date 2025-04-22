/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:09:04 by msalaibb          #+#    #+#             */
/*   Updated: 2025/04/21 22:05:16 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_split(char **cmds)
{
	int i = 0;

	while (cmds[i] != NULL)
	{
		ft_putstr_fd("==============\n\n", debug_fd());
		ft_putstr_fd("Palavrinha magica: ", debug_fd());
		ft_putstr_fd(cmds[i], debug_fd());
		ft_putstr_fd("\n\n", debug_fd());
		i++;
	}
}

int	debug_fd(void)
{
	static int fd = -1;
	
	if (fd == -1)
		fd = open("debug.txt", O_WRONLY | O_TRUNC | O_CREAT, 0777);
	return (fd);
}

void	print_cmds(void)
{
	t_cmds *new_cmds;
	t_flags *TRT;

	new_cmds = get_t_min()->cmds;
	while (new_cmds != NULL)
	{
		ft_putstr_fd("==============\n\n", debug_fd());
		ft_putstr_fd("Comando: ", debug_fd());
		ft_putstr_fd(new_cmds->cmd, debug_fd());
		ft_putstr_fd("\n", debug_fd());
		ft_putstr_fd("Quote: ", debug_fd());
		ft_putnbr_fd(new_cmds->quote, debug_fd());
		ft_putstr_fd("\n\n", debug_fd());
		ft_putstr_fd("=====Flags====\n", debug_fd());
		TRT = new_cmds->flags;
		while (TRT != NULL)
		{
			ft_putstr_fd("Flag: ", debug_fd());
			if (TRT->flag == NULL)
				ft_putstr_fd("NULL", debug_fd());
			else
				ft_putstr_fd(TRT->flag, debug_fd());
			ft_putstr_fd("\nType: ", debug_fd());
			ft_putnbr_fd(TRT->quote, debug_fd());
			ft_putstr_fd("\n", debug_fd());
			TRT = TRT->next;
			if (TRT != NULL)
				ft_putstr_fd("---\n", debug_fd());
		}
		ft_putstr_fd("\n", debug_fd());
		ft_putstr_fd("Path: ", debug_fd());
		if (new_cmds->path != NULL)
			ft_putstr_fd(new_cmds->path, debug_fd());
		else
			ft_putstr_fd("Vazio", debug_fd());
		ft_putstr_fd("\n\n", debug_fd());
		new_cmds = new_cmds->next;
	}
}

void	print_env(char **env)
{
	int		i;

	i = -1;
	while (env[++i])
		printf("[i]: %d | [ENV]: %s\n", i, env[i]);
}
