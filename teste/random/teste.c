/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:25:37 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/23 15:47:45 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "gnl/get_next_line.h"

#define FILE_NAME "random"

int main(void)
{
	int		f_fd;
	char	*buffer;

	f_fd = open(FILE_NAME, O_RDONLY | O_CREAT, 0644);
	if (f_fd == -1)
	{
		perror ("Erro in f_fd open\n");
		return (1);
	}
	buffer = get_next_line(f_fd);
	printf ("BUFFER: %s, FD: %d\n", buffer, f_fd);
	while (buffer != NULL)
	{
		printf("[LOG]: %s\n", buffer);
		free(buffer);
		buffer = get_next_line(f_fd);
	}
	if (buffer)
		free (buffer);
	close (f_fd);
	write(1, "a\n\n", 3);
	f_fd = open (FILE_NAME, O_WRONLY | O_CREAT, 06444);
	if (f_fd == -1)
	{
		perror ("Erro in f_fd open\n");
		return (1);
	}
	buffer = get_next_line(f_fd);
	while (buffer != NULL)
	{
		printf("[LOG]: %s\n", buffer);
		free(buffer);
		buffer = get_next_line(f_fd);
	}
	if (buffer)
	free (buffer);
	close (f_fd);
	return (0);
}