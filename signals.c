/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 13:59:39 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/05 19:53:00 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_sh(int sig)
{
	t_min	*env;

	if (sig == SIGINT)
	{
		env = get_t_min();
		env->sig = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	sigquit_cmd(int sig)
{
	t_min	*env;

	if (sig == SIGQUIT)
	{
		env = get_t_min();
		env->sig = 131;
		write(1, "Quit (core dumped)\n", 20);
	}
}

static void	sigint_cmd(int sig)
{
	t_min	*env;

	if (sig == SIGINT)
	{
		env = get_t_min();
		env->sig = 130;
		write(1, "\n", 1);
	}
}

void	sig_cmd(void)
{
	signal (SIGINT, sigint_cmd);
	signal (SIGQUIT, sigquit_cmd);
}

void	sig_minishell(void)
{
	signal (SIGINT, sigint_sh);
	signal (SIGQUIT, SIG_IGN);
}
