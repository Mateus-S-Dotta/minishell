/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 18:45:23 by msalaibb          #+#    #+#             */
/*   Updated: 2025/04/07 22:05:08 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

	input = NULL;
	while (1)
	{
		input = readline("> ");
		if (ft_strncmp(f2->flag, input, ft_strlen(f2->flag)) == 0)
			break ;
		if (f2->quote == 0)
			expand_here_doc(&input);
		ft_putstr_fd(input, p_fd[1]);
		ft_putstr_fd("\n", p_fd[1]);
	}
	exit (1);
}

void	open_here_doc(t_flags *f2)
{
	pid_t	pid;
	int		p_fd[2];

	if (f2 == NULL || f2->flag == NULL)
		free_all("bash: syntax error near unexpected token newline\n", 1);
	if (pipe(p_fd) == -1)
		free_all("Pipe Error\n", 1);
	dup_func(get_t_min()->in_fd, 0, get_t_min()->out_fd, 1);
	pid = fork();
	if (pid == -1)
		exit_error_minishell("Unable to open heredoc", 5);
	if (pid == 0)
		open_node(f2, p_fd);
	else
	{
		wait(&pid);
		dup_func(p_fd[0], 0, -1, -1);
		close_all(p_fd[0], p_fd[1]);
		free_flag(f2);
	}
}

int	there_is_heredok(char **cmd, int i)
{
	if (i == 0)
		return (1);
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
