/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:37:18 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/26 21:49:07 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ch_path(char **env, char *field, char *new_value_field)
{
	int		i;
	int		s_field;
	char	*tmp_str;
	char	*new_str;

	i = -1;
	s_field = ft_strlen(field);
	while (env[++i])
	{
		if (ft_strncmp(field, env[i], s_field) == 0 && env[i][s_field] == '=')
		{
			new_str = ft_strndup(env[i], s_field + 1);
			tmp_str = new_str;
			new_str = ft_strjoin(new_str, new_value_field);
			free(env[i]);
			env[i] = new_str;
			return (free(tmp_str), 1);
		}
	}
	return (0);
}

static char	*take_field_value(char **env, char *field)
{
	int		i;
	int		fl_s;
	char	*f_val;

	i = -1;
	f_val = NULL;
	fl_s = ft_strlen(field);
	while (env[++i])
	{
		if (ft_strncmp(env[i], field, fl_s) == 0 && env[i][fl_s] == '=')
		{
			f_val = (char *)malloc(1 * ft_strlen(&env[i][fl_s + 1]) + 1);
			if (!f_val)
				return (NULL);
			ft_strlcpy(f_val, &env[i][fl_s + 1], 1024);
			return (f_val);
		}
	}
	return (NULL);
}

static int	go_home(char **env)
{
	char	*crr_pwd;
	char	*home_pwd;

	crr_pwd = take_field_value(env, "PWD");
	home_pwd = take_field_value(env, "HOME");
	ch_path(env, "OLDPWD", crr_pwd);
	ch_path(env, "PWD", home_pwd);
	if (chdir(home_pwd) != 0)
	{
		printf ("bash: cd: %s: No such file or directory\n", home_pwd);
		return (free(crr_pwd), free(home_pwd), 0);
	}
	
	return (free(crr_pwd), free(home_pwd), 1);
}

static int	go_to(char **env, char *path)
{
	char	*crr_pwd;
	char	*new_pwd;

	if (chdir(path) != 0)
	{
		printf ("bash: cd: %s: No such file or directory\n", path);
		return (0);
	}
	new_pwd = (char *)malloc(sizeof(char) * 256);
	getcwd(new_pwd, 256);
	crr_pwd = take_field_value(env, "PWD");
	ch_path(env, "OLDPWD", crr_pwd);
	ch_path(env, "PWD", new_pwd);
	return (free(crr_pwd), free(new_pwd), 0);
}

int	ft_cd(t_cmds *cmds, char ***env)
{
	int		cod;

	if (!cmds->flags)
	{
		cod = go_home(*env);
		int_env_file(*env);
		return (cod);
	}
	if (cmds->flags->next)
		printf("minishell: cd: too many arguments\n");
	cod = go_to(*env, cmds->flags->flag);
	int_env_file(*env);
	if (!cod)
		return (1);
	return (0);
}