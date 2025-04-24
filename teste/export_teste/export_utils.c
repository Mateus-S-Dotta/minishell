/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 19:37:53 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/23 19:54:41 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

int	open_file(char *file_name, int type)
{
	int	fd;

	fd = open(file_name, type, 0644);
	if (fd == -1)
	{
		perror("Error opening file");
		return (-1);
	}
	return (fd);
}

void	free_splited(char **splited)
{
	int		i;

	if (!splited)
		return;
	i = -1;
	while (splited[++i])
		free(splited[i]);
	free(splited);
	splited = NULL;
}

int	cnt_env(void)
{
	int		fd_f;
	int		count;
	char	*line_gnl;

	fd_f = open_file(FILE_NAME, O_RDONLY);
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