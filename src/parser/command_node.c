/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 00:49:01 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/05/07 13:01:33 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	create_cmds(t_cmds *cmds, char **cmd_w, int d)
{
	int		i;
	t_cmds	*new_cmds;

	if (ft_strncmp(cmd_w[d], "|", 1) == 0)
	{
		free_split(cmd_w);
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		minishell();
	}
	i = 0;
	while (cmd_w[i + d] != NULL && ft_strncmp(cmd_w[i + d], "|", 1) != 0) // count how many token constitute a single command
		i++;
	new_cmds = (t_cmds *)malloc(sizeof(t_cmds));
	if (new_cmds == NULL)
		exit_error_minishell("Malloc Error\n", 1);
	//atualiza os tokens baseado nas aspas simples e dupls e retorna se ele esta ou nao em aspas
	new_cmds->quote = unify(d - 1, cmd_w); // simples = 2 | double = 1 | none = 0
	//after update the token(s) based into their quoutes it copy to the final struct
	new_cmds->cmd = ft_strdup(cmd_w[d]);
	if (new_cmds->cmd == NULL)
		free_normal_comand(new_cmds, cmd_w);
	new_cmds->path = NULL;
	new_cmds->next = NULL;
	new_cmds->flags = NULL;
	// create the whole strcut of cmd and flags in a recursive way
	copy_verify(cmds, new_cmds, cmd_w, d + 1); 
}

void	free_normal_comand(t_cmds *new_cmds, char **cmd_w)
{
	t_flags	*flags;

	if (new_cmds == NULL)
		return ;
	flags = new_cmds->flags;
	while (flags != NULL)
	{
		if (flags->flag != NULL)
			free(flags->flag);
		free(flags);
	}
	if (new_cmds->cmd != NULL)
		free(new_cmds->cmd);
	if (new_cmds->path != NULL)
		free(new_cmds->path);
	free_split(cmd_w);
	free_all("Command Not Found\n", 1);
}
