/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalaibb <msalaibb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:01:13 by msalaibb          #+#    #+#             */
/*   Updated: 2025/03/14 16:45:56 by msalaibb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	inicialize(char *env[])
{
	get_t_min()->in_fd = dup(0);
	get_t_min()->out_fd = dup(1);
	get_t_min()->env = env;
}

t_min	*get_t_min(void)
{
	static t_min	min;

	return (&min);
}

void	minishell(void)
{
	char	*input;
	pid_t	process;
	int		status;

	input = readline("minishell> ");
	if (!input)
		return ;
	if (verify_spaces(input))
		return (free(input), minishell());
	if (ft_strncmp(input, "exit", 4) == 0 && ft_strlen(input) == 4)
		return (free(input));
	process = fork();
	if (process == -1)
		exit_error_minishell("Error Fork\n", 1);
	if (process == 0)
		normal_comand(input);
	else
	{
		waitpid(process, &status, 0);
		if (!WIFEXITED(status))
			free_all(NULL, -1);
		restart_shell(input);
	}
}

void	restart_shell(char *str)
{
	add_history(str);
	free(str);
	if (dup2(get_t_min()->in_fd, 0) == -1)
		return ;
	if (dup2(get_t_min()->out_fd, 1) == -1)
		return ;
	minishell();
}

int	main(int argc, char *argv[], char *env[])
{
	(void)argc;
	(void)argv;
	inicialize(env);
	minishell();
	return (0);
}
