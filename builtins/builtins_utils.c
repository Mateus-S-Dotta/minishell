/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 20:44:31 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/16 03:02:18 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void exec_builtins(t_cmds *cmds);
int	is_builtins(char *cmd);

static char	**builtins_arr(void)
{
	char	**btarr;

	btarr = (char **)malloc(8 * sizeof(char *));
	if (!btarr)
		return (NULL);
	btarr[0] = ft_strdup("echo");
	btarr[1] = ft_strdup("cd");
	btarr[2] = ft_strdup("pwd");
	btarr[3] = ft_strdup("export");
	btarr[4] = ft_strdup("unset");
	btarr[5] = ft_strdup("env");
	btarr[6] = ft_strdup("exit");
	btarr[7] = NULL;
	
	return (btarr);
}

static void	builtins_free(char **arr_builtins)
{
	int		i;

	i = -1;

	if (!arr_builtins)
		return;
	while (arr_builtins[++i])
		free (arr_builtins[i]);
	free(arr_builtins);
}

int	is_builtins(char *cmd)
{
	char	**btarr;
	int		i;

	i = -1;
	btarr = builtins_arr();
	while (btarr[++i])
	{
		if (ft_strncmp(cmd, btarr[i], ft_strlen(btarr[i]) + 1) == 0)
		{
			builtins_free(btarr);
			return (1);
		}
	}
	builtins_free(btarr);
	return (0);
}

void exec_builtins(t_cmds *cmds)
{
	char	**btarr;
	t_min	*env;

	env  = get_t_min();
	btarr = builtins_arr();
	if (!cmds)
		return ;
	if (ft_strncmp(cmds->cmd, btarr[0], ft_strlen(cmds->cmd)) == 0)
		env->sig = ft_echo(cmds);
	// else if (ft_strncmp(cmds->cmd, btarr[1], ft_strlen(btarr[1])))
	// 	env->sig = ft_cd(cmds);
	// else if (ft_strncmp(cmds->cmd, btarr[2], ft_strlen(btarr[2])))
	// 	env->sig = ft_pwd(cmds);
	// else if (ft_strncmp(cmds->cmd, btarr[3], ft_strlen(btarr[3])))
	// 	env->sig = ft_export(cmds);
	// else if (ft_strncmp(cmds->cmd, btarr[4], ft_strlen(btarr[4])))
	// 	env->sig = ft_unset(cmds);
	// else if (ft_strncmp(cmds->cmd, btarr[5], ft_strlen(btarr[5])))
	// 	env->sig = ft_env(cmds);
	// else if (ft_strncmp(cmds->cmd, btarr[6], ft_strlen(btarr[6])))
	// 	env->sig = ft_exit(cmds);
	builtins_free(btarr);
}