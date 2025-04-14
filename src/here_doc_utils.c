/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:27:50 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/14 19:30:51 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_hd(int sig)
{
	t_min	*env;

	if (sig == SIGINT)
	{
		ft_putstr_fd("triger\n", debug_fd());
		env = get_t_min();
		env->sig = 130;
		write(1, "\n", 1);
	}
	exit(130);
}

void	std_hd_sig(void)
{
	signal(SIGINT, sigint_hd);
}
