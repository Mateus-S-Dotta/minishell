/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 18:45:23 by msalaibb          #+#    #+#             */
/*   Updated: 2025/05/11 00:34:43 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expand_here_doc(char **input)
{
	int	i;

	i = -1;
	while (input[0][++i] != '\0')
		if (input[0][i] == '$')
			verify_money(input, &i);
}

void	dup_func(int fd1, int fd2, int fd3, int fd4)
{
	if (dup2(fd1, fd2) == -1)
		free_all("Dup2 Error\n", 1);
	if (fd3 == -1)
		return ;
	if (dup2(fd3, fd4) == -1)
		free_all("Dup2 Error\n", 1);
}

void	find_all_here_doc(t_cmds *cmd, int *c)
{
	t_flags	*flags;

	flags = cmd->flags;
	if (ft_strncmp(cmd->cmd, "<<", 2) == 0)
	{
		open_here_doc(flags);
		free(cmd->cmd);
		cmd->cmd = NULL;
	}
	while (flags != NULL)
	{
		if (flags->flag != NULL && ft_strncmp(flags->flag, "<<", 2) == 0
			&& flags->next != NULL)
		{
			open_here_doc(flags->next);
			free(flags->flag);
			flags->flag = NULL;
			c[0] = 1;
		}
		flags = flags->next;
	}
}

static void	open_node(t_flags *f2, int *p_fd)
{
	char	*input;
	char	*hate_norm;

	input = NULL;
	hate_norm = "at line 14 delimited by end-of-file (wanted `EOF')\n";
	while (1)
	{
		std_hd_sig();
		input = readline("> ");
		if (!input)
		{
			ft_putstr_fd("Minishell: warning: here-document ", 1);
			ft_putstr_fd(hate_norm, 1);
			exit (EXIT_FAILURE);
		}
		if (ft_strncmp(f2->flag, input, ft_strlen(f2->flag)) == 0)
			break ;
		if (f2->quote == 0)
			expand_here_doc(&input);
		ft_putstr_fd(input, p_fd[1]);
		ft_putstr_fd("\n", p_fd[1]);
	}
}

void	open_here_doc(t_flags *f2)
{
	int		p_fd[2];

	if (f2 == NULL || f2->flag == NULL)
		free_all("bash: syntax error near unexpected token newline\n", 1);
	if (pipe(p_fd) == -1)
		free_all("Pipe Error\n", 1);
	dup_func(get_t_min()->in_fd, 0, get_t_min()->out_fd, 1);
	open_node(f2, p_fd);
	dup_func(p_fd[0], 0, -1, -1);
	close_all(p_fd[0], p_fd[1]);
	free_flag(f2);
}
