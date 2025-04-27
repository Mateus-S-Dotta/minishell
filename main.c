/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:01:13 by msalaibb          #+#    #+#             */
/*   Updated: 2025/04/26 21:00:07 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_splited_env(char ***splited)
{
	int i;
	
	if (!*splited)
		return;
	
	i = -1;
	while ((*splited)[++i])
		free((*splited)[i]);
	
	free(*splited);
}

static char *get_crr_powd()
{
	char *cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd");
		return (NULL);
	}
	return (cwd);
}

static void	inicialize(char **env)
{
	get_t_min()->in_fd = dup(0);
	get_t_min()->out_fd = dup(1);
	get_t_min()->sig = 0;
	get_t_min()->pipe_cnt = 0;
	get_t_min()->src_pwd = get_crr_powd();
	int_env_file(env);
	get_t_min()->env = NULL;
}


static char	*jump_spaces(char *str) //! change this before
{
	int		i;

	i = 0;
	while (str[i] == ' ' ||  str[i] == '\t')
		i++;
	return (&str[i]);
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
		get_t_min()->env = update_env(&get_t_min()->env);
		input = readline("minishell> ");
		if (!input)
		{
			ft_putstr_fd("exiting\n", 1);
			free_split(get_t_min()->env);
			break ;
		}
		if (verify_spaces(input))
			continue ;
		if (!ft_strcmp(jump_spaces(input), "exit"))
		{
			free_split(get_t_min()->env);
			close_all(get_t_min()->in_fd, get_t_min()->out_fd);
			break ;
		}
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
