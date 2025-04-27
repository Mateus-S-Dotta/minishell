/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:59:39 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/27 16:48:21 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	sigint_sh(int sig);
void		set_std_sig(void);
void		set_std_cmd(void);
void		std_cmd_c(int sig);
void		std_cmd_back_slash(int sig);


//SHELL signal

static void	sigint_sh(int sig)
{
	t_min	*env;

	if (sig == SIGINT)
	{
		env = get_t_min();
		env->sig = 130;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		write(1, "\nminishell> ", 13);
	}
}

void	set_std_sig(void)
{
	struct sigaction	ctrl_c;

	ft_memset(&ctrl_c, 0, sizeof(ctrl_c));
	ctrl_c.sa_handler = sigint_sh;
	ctrl_c.sa_flags = SA_RESTART;
	sigaction(SIGINT, &ctrl_c, NULL);
	signal(SIGQUIT, SIG_IGN);
}
// CMD signal

void	set_std_cmd(void)
{
	signal(SIGINT, std_cmd_c);
	signal(SIGQUIT, std_cmd_back_slash);
}

void	std_cmd_c(int sig)
{
	t_min	*env;

	if (sig == SIGINT)
	{
		env = get_t_min();
		env->sig = 130;
		write(1, "\n", 1);
	}
}

void	std_cmd_back_slash(int sig)
{
	t_min	*env;

	if (sig == SIGQUIT)
	{
		env = get_t_min();
		env->sig = 131;
		write(1, "Quit (core dumped)\n", 20);
	}
}
