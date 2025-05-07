/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   super_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:10:05 by msalaibb          #+#    #+#             */
/*   Updated: 2025/05/07 12:07:17 by lsilva-x         ###   ########.fr       */
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
		if (is_word(cmd, i)) //verify if the current position is somehting as a letter
		{
			find = 1;
			count++;
		}
		while (is_word(cmd, i)) //while is condition is true still consider as the same word
			i++;
		/*jump_quoutes trata os casos onde um palavra comeca com aspas simples ou duplas
		ou se ela e encontra no meio da palavra, e continua a contagem de token das mesma
		forma
		
		outro "hello" -> pos "outro" a palavra "hello" cairia direto nessa funcao
		m"an"ga -> ou nesse caso onde temos aspas duplas dentro da mesma palavra
		*/
		jump_quotes(cmd, &i, &count, find);
		/*trata os casos espeicias como redirects, heredoc e pipes que podem estar
		colada a uma palavra e devem ser considerados na contagem tambem
		
		cat<<eof|ls -> a contagem segue correta, 5 tokens
		*/
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

	max = count_s_s(cmd); //faz a contagem da quantidades de tokens que tem no comando
	split = (char **)calloc(max + 1, sizeof(char *));
	if (split == NULL)
		exit_error_minishell("Malloc Error\n", 1);
	i = -1;
	j = 0;
	while (cmd[j] == ' ')
		j++;
	while (++i < max)
		if (cmd[j] == '|')
			pipe_case(split, cmd, &j, i); //copy the pipe as a whole token
		else
		{
			//count_letter aplica a mesma logica de count_s_s pra contar o tamanho do token(em char)
			split[i] = (char *)calloc(count_letter(cmd, j) + 1, sizeof(char *));
			copy_str(split[i], cmd, &j); //copia toda a str e as aspas duplas e simples que tiverem no token tambem
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
	//Recieve the char * with the expansion already done
	cmds_w = super_split(cmd);
	free(cmd);
	if (cmds_w == NULL)
		exit_error_minishell("Malloc Error\n", 1);
	return (cmds_w);
}
