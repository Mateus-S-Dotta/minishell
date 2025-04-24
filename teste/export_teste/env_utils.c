/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 19:39:31 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/24 03:04:32 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

char	**update_env(char **env)
{
	int		i;
	int		fd_f;
	char	*line_gnl;
	char	**new_env;

	i = -1;
	free_splited(env);
	new_env = (char **)malloc(sizeof(char *) * (cnt_env() + 1));
	if (!new_env)
		return (perror ("Malloc env** error\n"), NULL);
	fd_f = open_file(FILE_NAME, O_RDONLY);
	if (fd_f == -1)
		return (NULL);
	line_gnl = get_next_line(fd_f);
	while (line_gnl)
	{
		new_env[++i] = ft_strdup(line_gnl);
		free(line_gnl);
		line_gnl = get_next_line(fd_f);
	}
	new_env[++i] = NULL;
	close(fd_f);
	return (new_env);
}

static int	has_equal(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
		{
			if (str[i + 1] == '\0')
				return (1);
			return (2);
		}
	}
	return (0);
}
char	*create_env_entry(char **values, char *input)
{
	char	*new_entry;
	char	*temp;
	int		i;
	int		res;

	i = 0;
	res = has_equal(input);
	new_entry = ft_strdup(values[0]);
	if (!new_entry)
		return (NULL);
	if (res)
	{
		temp = new_entry;
		if (res == 1)
			new_entry = ft_strjoin(new_entry, "=\"\"");
		else
			new_entry = ft_strjoin(new_entry, "=");
		free(temp);
		if (!new_entry)
			return (NULL);
	}
	while (values[++i])
	{
		temp = new_entry;
		new_entry = ft_strjoin(new_entry, values[i]);
		free(temp);
		if (!new_entry)
			return (NULL);
	}
	return (new_entry);
}

char	**add_or_update_env(char **values, char **env, char *new_entry)
{
	int		fd_f;
	int		found;
	char	*line_gnl;
	char	**new_env;
	int		i;

	found = 0;
	i = 0;
	fd_f = open_file(FILE_NAME, O_RDONLY);
	new_env = (char **)malloc(sizeof(char *) * (cnt_env() + 2));
	line_gnl = get_next_line(fd_f);
	while (line_gnl)
	{
		line_gnl[strlen(line_gnl) - 1] = '\0';
		if (!found && !strncmp(line_gnl, values[0], strlen(values[0])))
		{
			new_env[i++] = ft_strdup(new_entry);
			found = 1;
		}
		else
			new_env[i++] = ft_strdup(line_gnl);
		free(line_gnl);
		line_gnl = get_next_line(fd_f);
	}
	if (!found && strlen(new_entry))
		new_env[i++] = ft_strdup(new_entry);
	new_env[i] = NULL;
	close(fd_f);
	return (new_env);
}

char	**copy_env(char **env)
{
	int		i;
	int		count;
	char	**new_env;
	char	*tmp_env;

	count = 0;
	while (env[count])
		count++;
	new_env = (char **)malloc((count + 1) * sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			while (--i >= 0)
				free(new_env[i]);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[count] = NULL;
	return (new_env);
}