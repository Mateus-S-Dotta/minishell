/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalaibb <msalaibb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:01:12 by msalaibb          #+#    #+#             */
/*   Updated: 2025/03/11 15:55:48 by msalaibb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env(char *c_env)
{
	int		aux;
	int		len;
	char	**env;

	aux = -1;
	env = get_t_min()->env;
	len = ft_strlen(c_env);
	while (env[++aux] != NULL)
		if (ft_strncmp(c_env, env[aux], len) == 0 && env[aux][len] == '=')
			break ;
	return (env[aux]);
}

char	*find_paths(char *cmd)
{
	int		aux;
	char	**paths;
	char	*full_path;
	char	*cmd_bar;

	aux = -1;
	if ((cmd[0] == '.' || cmd[0] == '/') && access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	paths = ft_split(get_env("PATH"), ':');
	if (paths == NULL)
		exit_error_minishell("Not Find Env\n", 1);
	cmd_bar = ft_strjoin("/", cmd);
	aux = -1;
	while (paths[++aux])
	{
		full_path = ft_strjoin(paths[aux], cmd_bar);
		if (access(full_path, X_OK | F_OK | R_OK) == 0)
			return (free(cmd_bar), free_split(paths), full_path);
		free(full_path);
	}
	return (free(cmd_bar), free_split(paths), NULL);
}
