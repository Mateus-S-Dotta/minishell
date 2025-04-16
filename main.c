/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:01:13 by msalaibb          #+#    #+#             */
/*   Updated: 2025/04/16 03:02:04 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	inicialize(char *env[])
{
	get_t_min()->in_fd = dup(0);
	get_t_min()->out_fd = dup(1);
	get_t_min()->sig = 0;
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

	while (1)
	{
		set_std_sig();
		input = readline("minishell> ");
		if (!input)
		{
			ft_putstr_fd("exiting\n", 1);
			break ;
		}
		if (verify_spaces(input))
			continue ;
		if (ft_strncmp(input, "exit", 4) == 0)
			break ;
		add_history(input);
		normal_comand(input);
		wait_last_status(get_t_min());
		free_all(NULL, -1);
		if (dup2(get_t_min()->in_fd, 0) == -1)
			return ;
		if (dup2(get_t_min()->out_fd, 1) == -1)
			return ;
	}
}

int	main(int argc, char *argv[], char *env[])
{
	(void)argc;
	(void)argv;
	inicialize(env);
	minishell();
	return (0);
}
