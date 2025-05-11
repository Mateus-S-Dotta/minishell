/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:01:12 by msalaibb          #+#    #+#             */
/*   Updated: 2025/05/11 20:56:11 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	write_in_file(int fd_f, char **env)
{
	int	i;

	i = -1;
	if (fd_f == -1 || !env)
		return ;
	while (env[++i])
	{
		if (write(fd_f, env[i], strlen(env[i])) == -1)
			break ;
		if (env[i][strlen(env[i]) - 1] != '\n')
		{
			if (write(fd_f, "\n", 1) == -1)
				break ;
		}
	}
}

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

static void	node_path(char **cmds)
{
	close_all(get_t_min()->in_fd, get_t_min()->out_fd);
	if (cmds)
		free(cmds);
	free_all("Not Find Env\n", 1);
}

char	*find_paths(char *cmd, char **cmds)
{
	int		aux;
	char	**paths;
	char	*full_path;
	char	*cmd_bar;

	aux = -1;
	if ((cmd[0] == '.' || cmd[0] == '/') && access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	paths = ft_split(ft_strchr(get_env("PATH"), '=') + 1, ':');
	if (paths == NULL)
		node_path(cmds);
	if (is_builtins(cmd, 7))
		return (free_split(paths), NULL);
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
