/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:37:18 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/19 20:04:22 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//TODO -> a single `cd` must go to the `~` dir

void	old_pwd(char *old_pwd, char **env)
{
	if (!old_pwd || !env)
		return ;
	
}

static int	change_value(char **env, char *field, char *new_value_field)
{
	int		i;
	char	*tmp_env;
	char	*new_str;
	
	i = -1;
	if (!new_value_field || !env || !*env || field)
		return (0);
	while (env[++i])
	{
		if (strncmp(field, env[i], strlen(field)) == 0 && env[i][strlen(field)] == '=')
		{
			tmp_env = env[i];
			new_str = ft_strdup(new_value_field);
			if (!new_str)
				return (0);
			env[i] = new_str;
			free(tmp_env);
			return (1);
		}
	}
}

static int go_to_home()
{
	old_pwd();
}

int	fd_cd(t_cmds	*cmd)
{
	if (!cmd->flags->flag)
		go_to_home();
}