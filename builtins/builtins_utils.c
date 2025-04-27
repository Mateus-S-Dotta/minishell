/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 20:44:31 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/26 21:49:58 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_builtins(t_cmds *cmds);

static char	**builtins_arr(void)
{
	char	**btarr;

	btarr = (char **)malloc(8 * sizeof(char *));
	if (!btarr)
		return (NULL);
	btarr[0] = ft_strdup("cd");
	btarr[1] = ft_strdup("export");
	btarr[2] = ft_strdup("unset");
	btarr[3] = ft_strdup("echo");
	btarr[4] = ft_strdup("pwd");
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
		return ;
	while (arr_builtins[++i])
		free (arr_builtins[i]);
	free(arr_builtins);
}

int	is_builtins(char *cmd, int range)
{
	char	**btarr;
	int		i;

	i = -1;
	btarr = builtins_arr();
	while (++i < range)
		if (ft_strncmp(cmd, btarr[i], ft_strlen(btarr[i]) + 1) == 0)
			return (builtins_free(btarr), 1);
	return (builtins_free(btarr), 0);
}

void	exec_builtins(t_cmds *cmds)
{
	char	**btarr;
	int		cmd_s;
	t_min	*env;

	env = get_t_min();
	cmd_s = ft_strlen(cmds->cmd);
	btarr = builtins_arr();
	if (!cmds)
		return ;
	else if (!ft_strncmp(cmds->cmd, btarr[0], cmd_s))
		env->sig = ft_cd(cmds, &get_t_min()->env);
	else if (!ft_strncmp(cmds->cmd, btarr[1], cmd_s))
		env->sig = ft_export(cmds, &get_t_min()->env);
	else if (!ft_strncmp(cmds->cmd, btarr[2], cmd_s))
		env->sig = ft_unset(cmds, &get_t_min()->env);
	else if (!ft_strncmp(cmds->cmd, btarr[3], cmd_s))
		env->sig = ft_echo(cmds);
	else if (!ft_strncmp(cmds->cmd, btarr[4], cmd_s))
		env->sig = ft_pwd();
	else if (!ft_strncmp(cmds->cmd, btarr[5], cmd_s))
		env->sig = ft_env();
	else if (!ft_strncmp(cmds->cmd, btarr[5], cmd_s))
		return ;
	builtins_free(btarr);
}
