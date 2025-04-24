/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_teste.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 00:34:54 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/24 02:56:06 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

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
		if (write(fd_f, "\n", 1) == -1)
			break ;
	}
}

int	ft_export(char *input, char **env)
{
	char	**s_input;
	char	**new_env;
	char	*new_entry;
	int		fd_f;

	//TODO this must be modify to comport the struct from minishel
	if (!strcmp(input, "export"))
		return (print_in_order(env), 0);
	s_input = ft_split(input + strlen("export "), '=');
	new_entry = create_env_entry(s_input, input);
	new_env = add_or_update_env(s_input, env, new_entry);
	fd_f = open_file(FILE_NAME, O_WRONLY);
	write_in_file(fd_f, new_env);
	return (free_splited(new_env), free(new_entry), close(fd_f), 0);
}

int main(int argc, char **argv, char **env)
{
	char	*input;
	int		fd;
	char	**env_cpy;

	env_cpy = NULL;
	input = NULL;
	write_in_file(open_file(FILE_NAME, O_WRONLY), env);
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
		free(input);
	}
	return (0);
}

/*
export A | export only
export A= | env
export A=abc | env

*/