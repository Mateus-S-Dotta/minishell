/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   super_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:10:05 by msalaibb          #+#    #+#             */
/*   Updated: 2025/05/06 17:52:55 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	count_s_s(char *cmd)
{
	int		i;
	int		count;
	int		find;

	i = 0;
	count = 0;
	while (cmd[i] != '\0' && cmd[i] == 32)
		i++;
	while (cmd[i] != '\0')
	{
		find = 0;
		if (is_word(cmd, i))
		{
			find = 1;
			count++;
		}
		while (is_word(cmd, i))
			i++;
		jump_quotes(cmd, &i, &count, find);
		jump_all(cmd, &i, &count);
	}
	return (count);
}

static char	**super_split(char *cmd)
{
	char	**split;
	int		i;
	int		max;
	int		j;

	max = count_s_s(cmd);
	split = (char **)calloc(max + 1, sizeof(char *));
	if (split == NULL)
		exit_error_minishell("Malloc Error\n", 1);
	i = -1;
	j = 0;
	while (cmd[j] == ' ')
		j++;
	while (++i < max)
		if (cmd[j] == '|')
			pipe_case(split, cmd, &j, i);
	else
	{
		split[i] = (char *)calloc(count_letter(cmd, j) + 1, sizeof(char *));
		copy_str(split[i], cmd, &j);
	}
	return (split);
}

static void	count_quote(int *count, int *in_quotes, int i, int j)
{
	count[i] += 1;
	*in_quotes = j;
}

static void	find_quote(char **cmd)
{
	int	i;
	int	count[2];
	int	in_quotes;

	i = -1;
	count[0] = 0; // single quoute
	count[1] = 0; //double quoute
	in_quotes = 0;
	while (cmd[0][++i] != '\0')
	{
		if (cmd[0][i] == '$' && in_quotes != 1)
			verify_money_start(cmd, &i, &in_quotes, count);
		else if (cmd[0][i] == '\"' && in_quotes == 0)
			count_quote(count, &in_quotes, 1, 2); //find " = 2
		else if (cmd[0][i] == '\'' && in_quotes == 0)
			count_quote(count, &in_quotes, 0, 1); //find ' = 1
		else if (cmd[0][i] == '\'' && in_quotes == 1)
			count_quote(count, &in_quotes, 0, 0); //close ' = 0
		else if (cmd[0][i] == '\"' && in_quotes == 2)
			count_quote(count, &in_quotes, 1, 0); //cloe " = 0
	}
	if (count[0] % 2 != 0 || count[1] % 2 != 0) // no closed quoute
	{
		ft_putstr_fd("No Closed quote\n", 2);
		minishell();
	}
}

char	**super_ft_split(char *cmd)
{
	int		i;
	char	**cmds_w;

	find_quote(&cmd); //verify if every single and double quoute is closed and expand under N conditions
	i = 0;
	while (cmd[i] != '\0' && (cmd[i] == 32 || cmd[i] == '\''
			|| cmd[i] == '\"'))
		i++;
	if (cmd[i] == '\0') // expand nothing
	{
		free(cmd);
		minishell();
	}
	cmds_w = super_split(cmd);
	free(cmd);
	if (cmds_w == NULL)
		exit_error_minishell("Malloc Error\n", 1);
	return (cmds_w);
}
