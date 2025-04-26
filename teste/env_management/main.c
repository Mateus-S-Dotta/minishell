/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:41:54 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/25 15:22:32 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
		env_cpy = update_env(&env_cpy);
		input = readline("minishell> ");
		if (!input || !strcmp(input, "exit"))
		{
			free_splited(&env_cpy);
			break;
		}
		if (*input)
			add_history(input);
		if (!strncmp(input, "export", strlen("export")))
			ft_export(input, &env_cpy);
		else if (!strncmp(input, "env", strlen("env")))
			ft_env(env_cpy);
		else if (!strncmp(input, "unset", strlen("unset")))
			ft_unset(input, env_cpy);
		else if (!strncmp(input, "cd", strlen("cd")))
			ft_cd(input, env_cpy);
		free(input);
	}
	if (input)
		free (input);
	return (0);
}