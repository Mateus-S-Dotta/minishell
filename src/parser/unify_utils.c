/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unify_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:42:13 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/05/11 16:47:35 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	process_char(char current_char, char *quote, int *num, char *new);
char	*init_val(int *num, int i, char **cmd, char quote);
int		max_count(int i, char **cmds);

int	max_count(int i, char **cmds)
{
	int	count;

	count = 0;
	while (cmds[++i] != NULL)
		count++;
	return (count);
}

char	*init_val(int *num, int i, char **cmd, char quote)
{
	char	*new;

	num[4] = max_count(i, cmd);
	num[3] = i;
	new = (char *)ft_calloc(count_unify(num[3], cmd, quote) + 1, sizeof(char));
	if (new == NULL)
		exit_error_minishell("Malloc Error", 1);
	num[0] = 0;
	num[1] = 0;
	num[2] = -1;
	return (new);
}

void	process_char(char current_char, char *quote, int *num, char *new)
{
	if (current_char == *quote)
		num[0]++;
	else if ((current_char == '\'' || current_char == '\"') && num[0] % 2 == 0)
	{
		*quote = current_char;
		num[0]++;
	}
	else
		new[num[1]++] = current_char;
}
