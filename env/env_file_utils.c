/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_file_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:37:58 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/25 16:31:02 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		int_env_file(char **env);
int		open_file(char *file_name, int oflag);
void	write_in_file(int fd_f, char **env);
char	**update_env(char ***env);

int	open_file(char *file_name, int oflag)
{
	int	fd;

	fd = open(file_name, oflag, 0644);
	if (fd == -1)
		return (perror("Error opening file"), -1);
	return (fd);
}

int	int_env_file(char **env)
{
	int		fd_f;

	fd_f = open(FILE_NAME, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd_f == -1)
		return (perror ("Failed in open file"), -1);
	write_in_file(fd_f, env);
	close (fd_f);
	return (0);
}

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

char	**update_env(char ***env)
{
	int i;
	int fd_f;
	char *line_gnl;
	char **new_env;
	
	i = -1;
	if (*env != NULL)
		free_splited_env(env);
	new_env = (char **)malloc(sizeof(char *) * (cnt_env() + 1));
	if (!new_env)
		return (perror("Malloc env** error\n"), NULL);
	
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

int	cnt_env(void)
{
	int		fd_f;
	int		count;
	char	*line_gnl;

	count = 0;
	fd_f = open_file(FILE_NAME, O_RDONLY);
	if (fd_f == -1)
		return (-1);
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