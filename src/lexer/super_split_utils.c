/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   super_split_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 22:16:52 by msalaibb          #+#    #+#             */
/*   Updated: 2025/04/27 16:56:01 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	copy_quotes_copy(char *split, char *cmd, int *j, int *i_copy)
{
	split[*i_copy] = cmd[*j];
	*i_copy += 1;
	*j += 1;
}

static void	copy_quotes(char *split, char *cmd, int *j, int *i_copy)
{
	char	quote;

	while (cmd[*j] != '\0' && (cmd[*j] == '\'' || cmd[*j] == '\"'))
	{
		quote = cmd[*j];
		copy_quotes_copy(split, cmd, j, i_copy);
		while (cmd[*j] != '\0' && cmd[*j] != quote)
			copy_quotes_copy(split, cmd, j, i_copy);
		if (cmd[*j] != '\0' && (cmd[*j] == '\'' || cmd[*j] == '\"'))
			copy_quotes_copy(split, cmd, j, i_copy);
		while (is_word(cmd, *j))
			copy_quotes_copy(split, cmd, j, i_copy);
	}
}

void	copy_str(char *split, char *cmd, int *j)
{
	int		i_copy;
	int		copyed;

	i_copy = 0;
	copyed = 0;
	while (is_word(cmd, *j))
	{
		copyed = 1;
		split[i_copy++] = cmd[*j];
		*j += 1;
	}
	if (cmd[*j] != '\0' && (cmd[*j] == '\'' || cmd[*j] == '\"'))
		copyed = 1;
	copy_quotes(split, cmd, j, &i_copy);
	while (copyed == 0 && cmd[*j] != '\0' && (cmd[*j] == '<' || cmd[*j] == '>'))
	{
		split[i_copy++] = cmd[*j];
		*j += 1;
	}
	while (cmd[*j] != '\0' && cmd[*j] == ' ')
		*j += 1;
}

void	pipe_case(char **split, char *cmd, int *j, int i)
{
	split[i] = (char *)calloc(2, sizeof(char));
	if (split[i] == NULL)
		return (free_split(split), exit_error_minishell("Malloc Error\n", 1));
	split[i][0] = '|';
	split[i][1] = '\0';
	*j += 1;
	while (cmd[*j] != '\0' && cmd[*j] == ' ')
		*j += 1;
}
