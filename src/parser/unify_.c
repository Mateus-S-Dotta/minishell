/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unify_.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 09:28:16 by msalaibb          #+#    #+#             */
/*   Updated: 2025/04/27 16:56:37 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	redefiny_split_unify(int i, int max, char **cmds)
{
	int	no_null;

	no_null = i + 1;
	if (cmds[no_null] != NULL)
		return ;
	while (no_null < max && cmds[no_null] == NULL)
		no_null++;
	while (cmds[no_null] != NULL)
	{
		cmds[i + 1] = cmds[no_null];
		cmds[no_null] = NULL;
		no_null++;
		i++;
	}
}

static int	count_unify(int i, char **cmd, char quote)
{
	int	j;
	int	pair;
	int	count;

	count = 0;
	pair = 0;
	while (cmd[++i] != NULL && (pair == 0 || pair % 2 != 0))
	{
		j = -1;
		while (cmd[i][++j] != '\0')
			if (cmd[i][j] != quote)
				count++;
		else
			pair++;
		if (cmd[i + 1] != NULL && (pair == 0 || pair % 2 != 0))
			count++;
	}
	return (count);
}

static int	max_count(int i, char **cmds)
{
	int	count;

	count = 0;
	while (cmds[++i] != NULL)
		count++;
	return (count);
}

// [3] = i_copy;
// [4] = max_initial_i;
static void	real_unify(int i, char **cmd, char quote)
{
	int		num[5];
	char	*new;

	num[4] = max_count(i, cmd);
	num[3] = i;
	new = (char *)ft_calloc(count_unify(num[3], cmd, quote) + 1, sizeof(char));
	if (new == NULL)
		exit_error_minishell("Malloc Error", 1);
	num[0] = 0;
	num[1] = 0;
	while (cmd[++i] != NULL && (num[0] == 0 || num[0] % 2 != 0))
	{
		num[2] = -1;
		while (cmd[i][++num[2]] != '\0')
			if (cmd[i][num[2]] != quote)
				new[num[1]++] = cmd[i][num[2]];
		else
			num[0]++;
		if (cmd[i + 1] != NULL && (num[0] == 0 || num[0] % 2 != 0))
			new[num[1]++] = ' ';
		free(cmd[i]);
		cmd[i] = NULL;
	}
	cmd[num[3] + 1] = new;
	redefiny_split_unify(num[3] + 1, num[4], cmd);
}

int	unify(int i, char **cmd)
{
	int		j;
	char	quote;

	j = -1;
	quote = '\0';
	while (cmd[i + 1][++j] != '\0')
	{
		if (cmd[i + 1][j] == '\'' || cmd[i + 1][j] == '\"')
		{
			if (cmd[i + 1][j] == '\'')
				quote = '\'';
			else
				quote = '\"';
			break ;
		}
	}
	if (quote != '\0')
	{
		real_unify(i, cmd, quote);
		if (quote == '\'')
			return (2);
		else
			return (1);
	}
	return (0);
}
