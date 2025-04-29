/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:01:07 by msalaibb          #+#    #+#             */
/*   Updated: 2025/04/29 15:43:38 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	verify_money_node(char *env_l, char **cmd, int i_init, int *i);

static void	redo_env(char **cmd, int init, int *i, char *env)
{
	char	*new_cmd;
	int		l[2];
	int		index;
	int		j;

	l[0] = ft_strlen(env);
	l[1] = ft_strlen(cmd[0]);
	new_cmd = (char *)ft_calloc(l[0] + l[1] - (*i - init) + 1, sizeof(char));
	if (new_cmd == NULL)
		exit_error_minishell("Malloc Error", 1);
	j = -1;
	while (++j < init)
		new_cmd[j] = cmd[0][j];
	index = -1;
	while (env[++index] != '\0')
		new_cmd[j + index] = env[index];
	j--;
	while (cmd[0][++j + (*i - init)] != '\0')
		new_cmd[j + index] = cmd[0][j + (*i - init)];
	free(cmd[0]);
	cmd[0] = new_cmd;
}

static void	money_copy(int *i, char **cmd, int i_initial, char *env_look)
{
	env_look[*i - i_initial - 1] = cmd[0][*i];
	*i += 1;
}

void	verify_money(char **cmd, int *i)
{
	char	*env_look;
	int		i_initial;
	char	*sig_ati;

	i_initial = *i;
	sig_ati = NULL;
	*i += 1;
	if (ft_isalpha(cmd[0][*i]) == 0 && cmd[0][*i] != '?')
		return (redo_env(cmd, i_initial, i, ""));
	else if (cmd[0][*i] == '?')
	{
		sig_ati = ft_itoa(get_t_min()->sig);
		return (*i += 1, redo_env(cmd, i_initial, i, sig_ati), free(sig_ati));
	}
	while ((ft_isalnum(cmd[0][*i]) || cmd[0][*i] == '_'))
		*i += 1;
	env_look = (char *)ft_calloc((*i - i_initial), sizeof(char));
	*i = i_initial + 1;
	while ((ft_isalnum(cmd[0][*i]) || cmd[0][*i] == '_'))
		money_copy(i, cmd, i_initial, env_look);
	verify_money_node(env_look, cmd, i_initial, i);
}

static void	verify_money_node(char *env_l, char **cmd, int i_init, int *i)
{
	char	*env;

	env = get_env(env_l);
	free(env_l);
	if (env == NULL)
		return (redo_env(cmd, i_init, i, ""));
	redo_env(cmd, i_init, i, &env[*i - i_init]);
	*i = 0;
}

void	verify_money_start(char **cmd, int *i, int *in_quote, int *count)
{
	if (there_is_heredok(cmd, *i))
		return ;
	if (ft_isalpha(cmd[0][*i + 1]) || cmd[0][*i + 1] == '?')
		verify_money(cmd, i);
	else
		return ;
	*in_quote = 0;
	*i = -1;
	count[0] = 0;
	count[1] = 0;
}
