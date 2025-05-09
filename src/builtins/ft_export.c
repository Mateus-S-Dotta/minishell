/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:20:25 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/05/09 02:57:28 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_input(char *str)
{
	int		i;
	char	*equal_sign;

	i = -1;
	while (str[++i] == ' ' || str[i] == '\t')
		continue ;
	equal_sign = ft_strchr(str, '=');
	if (equal_sign && ft_strchr(equal_sign + 1, '-'))
		return (1);
	if (ft_strchr(str, '-'))
		return (0);
	return (ft_isalpha(str[i]));
}

int	ft_export(t_cmds *cmds, char ***env)
{
	int		env_sts;
	char	*i_hate_norm;
	char	*str;

	if (!cmds->flags || cmds->flags->redirect == 1)
		return (print_in_order(*env), 0);
	if (get_t_min()->pipe_cnt != 1)
		return (0);
	str = cmds->flags->flag;
	i_hate_norm = ": not a valid identifier\n";
	if (!check_input(cmds->flags->flag))
	{
		ft_putstr_fd("minishell: export: `", 2);
		return (ft_putstr_fd(str, 2), ft_putstr_fd(i_hate_norm, 2), 1);
	}
	env_sts = env_searcher(str, *env);
	if (env_sts != -1)
		env_update(env, str, env_sts);
	else
		*env = env_create(*env, str);
	int_env_file(*env);
	return (0);
}
