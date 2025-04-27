/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   super_split_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 22:21:55 by msalaibb          #+#    #+#             */
/*   Updated: 2025/04/27 16:55:55 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_word(char *cmd, int i)
{
	return (cmd[i] != '\0' && cmd[i] != '<' && cmd[i] != '>'
		&& cmd[i] != '\'' && cmd[i] != '\"' && cmd[i] != 32
		&& cmd[i] != '|');
}

void	jump_quotes(char *cmd, int *i, int *count, int find)
{
	char	quote;

	while (cmd[*i] != '\0' && (cmd[*i] == '\'' || cmd[*i] == '\"'))
	{
		quote = cmd[*i];
		*i += 1;
		if (find == 0)
		{
			find = 1;
			*count += 1;
		}
		while (cmd[*i] != '\0' && cmd[*i] != quote)
			*i += 1;
		if (cmd[*i] != '\0' && (cmd[*i] == '\'' || cmd[*i] == '\"'))
			*i += 1;
		while (is_word(cmd, *i))
			*i += 1;
	}
}

void	jump_all(char *cmd, int *i, int *count)
{
	if (cmd[*i] != '\0' && (cmd[*i] == '<' || cmd[*i] == '>'))
		*count += 1;
	while (cmd[*i] != '\0' && (cmd[*i] == '<' || cmd[*i] == '>'))
		*i += 1;
	if (cmd[*i] != '\0' && cmd[*i] == '|')
	{
		*i += 1;
		*count += 1;
	}
	while (cmd[*i] != '\0' && cmd[*i] == 32)
		*i += 1;
}

int	count_letter(char *cmd, int j)
{
	int		initial_j;
	char	quote;

	initial_j = j;
	while (is_word(cmd, j))
		j++;
	while (cmd[j] != '\0' && (cmd[j] == '\'' || cmd[j] == '\"'))
	{
		quote = cmd[j];
		j += 1;
		while (cmd[j] != '\0' && cmd[j] != quote)
			j += 1;
		if (cmd[j] != '\0' && (cmd[j] == '\'' || cmd[j] == '\"'))
			j += 1;
		while (is_word(cmd, j))
			j += 1;
	}
	while (cmd[j] != '\0' && (cmd[j] == '<' || cmd[j] == '>'))
		j += 1;
	return (j - initial_j);
}
