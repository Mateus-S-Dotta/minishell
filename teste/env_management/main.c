/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:41:54 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/24 16:59:52 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	free_splited(char **splited) //? This function already exist in the main code
{
	int		i;

	if (!splited)
		return ;
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

int main(int argc, char **argv, char **env)
{
	char	*input;
	int		fd;
	char	**env_cpy;

	env_cpy = NULL;
	input = NULL;
	int_env_file(env);
	while (1)
	{
		env_cpy = update_env(env_cpy);
		input = readline("minishell> ");
		if (!input || !strcmp(input, "exit"))
			break;
		if (*input)
			add_history(input);
		if (!strncmp(input, "export", strlen("export")))
			ft_export(input, env_cpy);
		else if (!strncmp(input, "env", strlen("env")))
			ft_env(input, env_cpy);
		free(input);
	}
	return (0);
}