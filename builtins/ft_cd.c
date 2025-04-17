/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:21:35 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/17 15:38:27 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	old_pwd(char *old_pwd, char **env)
{
	
}

int	fd_cd(t_cmds *cmd)
{
	t_min	*env;
	char	crr_pd[256];

	env = get_t_min();
	if (!getcwd(crr_pd, 256))
		return (1);
	// old_pwd();
	if (!chdir(cmd->flags->flag))
		return (perror("cd"), 1);
	return (0);
}