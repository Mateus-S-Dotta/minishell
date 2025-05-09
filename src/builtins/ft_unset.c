/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:21:03 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/05/09 01:08:48 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_unset(t_cmds *cmds, char ***env)
{
	char	*str;
	int		env_sts;

	if (!cmds->flags)
		return (0);
	str = cmds->flags->flag;
	env_sts = env_searcher(str, *env);
	if (env_sts == -1)
		return (0);
	env_delete(env, env_sts);
	int_env_file(*env);
	return (0);
}
