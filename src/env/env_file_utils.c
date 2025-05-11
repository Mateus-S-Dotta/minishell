/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_file_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:37:58 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/05/11 20:56:01 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		int_env_file(char **env);
int		open_file(char *file_name, int oflag);
void	write_in_file(int fd_f, char **env);
char	**update_env(char ***env);

int	open_file(char *file_name, int oflag)
{
	int		fd;

	fd = open(file_name, oflag, 0644);
	if (fd == -1)
		return (perror("Error opening file"), -1);
	return (fd);
}

char	*env_tmp_relative(void)
{
	char	*tmp;
	char	*tmp2;
	char	*p_cwd;

	p_cwd = get_t_min()->p_cwd;
	tmp = ft_strjoin(p_cwd, "/");
	tmp2 = ft_strjoin(tmp, FILE_NAME);
	free(tmp);
	tmp = tmp2;
	return (tmp);
}

int	int_env_file(char **env)
{
	int		fd_f;
	char	*path;

	path = env_tmp_relative();
	fd_f = open_file(path, O_WRONLY | O_TRUNC | O_CREAT);
	free(path);
	if (fd_f == -1)
		return (perror ("Failed in open file"), -1);
	write_in_file(fd_f, env);
	close (fd_f);
	return (0);
}

char	**update_env(char ***env)
{
	int		i;
	int		fd_f;
	char	*line_gnl;
	char	*tmp;
	char	**new_env;

	i = -1;
	if (*env != NULL)
		free_splited_env(env);
	new_env = (char **)malloc(sizeof(char *) * (cnt_env() + 1));
	if (!new_env)
		return (perror("Malloc env** error\n"), NULL);
	tmp = env_tmp_relative();
	fd_f = open_file(tmp, O_RDONLY);
	line_gnl = get_next_line(fd_f);
	while (line_gnl)
	{
		line_gnl[ft_strlen(line_gnl) - 1] = '\0';
		new_env[++i] = ft_strdup(line_gnl);
		free(line_gnl);
		line_gnl = get_next_line(fd_f);
	}
	new_env[++i] = NULL;
	close(fd_f);
	return (free(tmp), new_env);
}

int	cnt_env(void)
{
	int		fd_f;
	char	*str_tmp;
	int		count;
	char	*line_gnl;

	count = 0;
	str_tmp = env_tmp_relative();
	fd_f = open_file(str_tmp, O_RDONLY);
	free(str_tmp);
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
