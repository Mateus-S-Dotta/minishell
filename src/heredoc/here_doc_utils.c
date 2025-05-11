/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:27:50 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/05/11 20:57:09 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sig_int_hd(int sig)
{
	t_min	*env;
	int		*ptr;

	ptr = set_heredoc_ptr(NULL, 1);
	if (sig == SIGINT)
	{
		env = get_t_min();
		env->sig = 130;
		write(1, "\n", 1);
	}
	close_all(ptr[0], ptr[1]);
	close_all(get_t_min()->pipe_ptr[0], get_t_min()->pipe_ptr[1]);
	free_all("", 130);
}

void	std_hd_sig(void)
{
	signal(SIGINT, sig_int_hd);
}

int	there_is_heredok(char **cmd, int i)
{
	if (i == 0)
	{
		if (cmd[0][0] == '$' && is_word(cmd[0], 1))
			return (0);
		return (1);
	}
	i--;
	while (i >= 0 && (cmd[0][i] == '\"' || cmd[0][i] == '\''))
		i--;
	while (i >= 0 && is_word(cmd[0], i))
		i--;
	while (i >= 0 && cmd[0][i] == ' ')
		i--;
	if (i >= 0 && cmd[0][i] == '<' && i - 1 >= 0 && cmd[0][i - 1] == '<')
		return (1);
	return (0);
}

int	*set_heredoc_ptr(int *ptr, int cod)
{
	static int	*ptr_static;

	if (cod == 0)
	{
		ptr_static = ptr;
		return (NULL);
	}
	return (ptr_static);
}
