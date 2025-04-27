/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:20:25 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/27 16:55:06 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	check_input(char *str)
{
	int		i;

	i = -1;
	while (str[++i] == ' ' || str[i] == '\t')
		continue ;
	return (ft_isalpha(str[i]));
}

int ft_export(t_cmds *cmds, char ***env)
{
	int		env_sts;
	char	*i_hate_norm;
	char	*str;

	if (!cmds->flags)
		return (print_in_order(*env), 0);
	str = cmds->flags->flag;
	i_hate_norm = ": not a valid identifier\n";
	if (!check_input(cmds->flags->flag))
	{
		printf("minishell: export: `%s`%s", str, i_hate_norm);
		return (1);
	}
	env_sts = env_searcher(str, *env);
	if (env_sts != -1)
		env_update(env, str, env_sts);
	else
		*env = env_create(*env, str);
	int_env_file(*env);
	return (0);
}