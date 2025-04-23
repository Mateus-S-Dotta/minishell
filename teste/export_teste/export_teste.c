/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_teste.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 00:34:54 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/23 15:53:42 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

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

int	open_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Error opening file");
		return (-1);
	}
	return (fd);
}

void	write_in_file(int fd_f, char **env)
{
	int	i;

	if (fd_f == -1 || !env)
		return;
	i = 0;
	while (env[i])
	{
		if (write(fd_f, env[i], strlen(env[i])) == -1 || write(fd_f, "\n", 1) == -1)
		{
			perror("Error writing to file");
			break;
		}
		i++;
	}
	close(fd_f);
}

void	free_splited(char **splited)
{
	int		i;

	i = -1;
	while (splited[++i])
		free(splited[i]);
	free(splited);
}

int	cnt_env(void)
{
	int		fd_f;
	int		count;
	char	*line_gnl;

	fd_f = open_file(FILE_NAME);
	if (fd_f == -1)
		return (-1);
	count = 0;
	line_gnl = get_next_line(fd_f);
	while (line_gnl)
	{
		count++;
		free(line_gnl);
		line_gnl = get_next_line(fd_f);
	}
	close(fd_f);
	return (count);
}

void	update_env(char **env)
{
	int		i;
	int		fd_f;
	char	*line_gnl;
	char	**new_env;
	
	i = -1;
	if (!env || !*env)
	{
		perror("Invalid arguments");
		return ;
	}
	fd_f = open_file(FILE_NAME);
	free_splited(env);
	new_env = (char **)malloc(sizeof(char *) * cnt_env());
	if (!new_env)
	{
		perror ("malloc env error\n");
		return ;
	}
	line_gnl = get_next_line(fd_f);
	while (line_gnl)
	{
		new_env[++i] = ft_strdup(line_gnl);
		free(line_gnl);
		line_gnl = get_next_line(fd_f);
	}
	return ;
}

void	add_or_update_env(char **values, char **env)
{
	int		fd_f;
	int		found;
	char	*line_gnl;
	char	*new_entry;
	char	**new_env;
	int		i, j;

	if (!values || !values[0] || !env)
	{
		perror("Invalid arguments");
		return;
	}
	fd_f = open_file(FILE_NAME);
	if (fd_f == -1)
		return;

	new_entry = ft_strdup(values[0]);
	new_entry = ft_strjoin(new_entry, "=");
	for (i = 1; values[i]; i++)
		new_entry = ft_strjoin(new_entry, values[i]);

	found = 0;
	i = 0;
	new_env = (char **)malloc(sizeof(char *) * (cnt_env() + 2));
	if (!new_env)
	{
		perror("malloc error");
		free(new_entry);
		close(fd_f);
		return;
	}
	line_gnl = get_next_line(fd_f);
	while (line_gnl)
	{
		if (!found && !strncmp(line_gnl, values[0], strlen(values[0])) && line_gnl[strlen(values[0])] == '=')
		{
			new_env[i++] = ft_strdup(new_entry);
			found = 1;
		}
		else
			new_env[i++] = ft_strdup(line_gnl);
		free(line_gnl);
		line_gnl = get_next_line(fd_f);
	}
	if (!found)
		new_env[i++] = ft_strdup(new_entry);
	new_env[i] = NULL;

	close(fd_f);
	fd_f = open_file(FILE_NAME);
	if (fd_f == -1)
	{
		free_splited(new_env);
		free(new_entry);
		return;
	}
	write_in_file(fd_f, new_env);
	free_splited(new_env);
	free(new_entry);
	close(fd_f);
}

void	ft_export(char *input, char **env)
{
	char	**s_input;

	
	if (!input || !env || !*env)
	{
		perror ("invalid input\n");
		return ;
	}
	//TODO this must be modify to comport the struct from minishel
	if (!strcmp(input, "export"))
	{
		print_in_order(env);
		return ;
	}
	s_input = ft_split(input + strlen("export "), '=');
	add_or_update_env(s_input, env);
}

int main(int argc, char **argv, char **env)
{
	char	*input;
	char	**env_cpy;

	if (!env || !*env)
		return (1);
	env_cpy = copy_env(env);
	write_in_file(open_file(FILE_NAME), env_cpy);
	while (1)
	{
		input = readline("minishell> ");
		if (!input || !strcmp(input, "exit"))
			break;
		if (*input)
			add_history(input);
		if (!strncmp(input, "export", strlen("export")))
			ft_export(input, env_cpy);
		free(input);
	}
	return (0);
}

/*
export A | export only
export A= | env
export A=abc | env

*/