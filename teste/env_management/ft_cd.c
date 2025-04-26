/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:08:15 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/25 15:33:27 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	go_home(char **env)
{
	int		env_pwd;
	int		env_old;
	char	**home_cd;
	char	**crr_cd;

	env_pwd = env_searcher("PWD", env);
	env_old = env_searcher("OLDPWD", env);
	home_cd = ft_split(env[env_searcher("HOME", env)], '=');
	home_cd[1][strlen(home_cd[1]) - 1] = '\0';
	crr_cd = ft_split(env[env_searcher("PWD", env)], '=');
	if (chdir(home_cd[1]) != 0)
	{	
		printf ("bash: cd: %s: No such file or directory\n", home_cd[1]);
		return (free_splited(&home_cd), free_splited(&crr_cd), 1);
	}
	if (env_pwd != -1)
		env_update(&env, home_cd, env_pwd);
	if (env_old != -1)
		env_update(&env, crr_cd, env_old);
	return (free_splited(&home_cd), free_splited(&crr_cd), 0);
}

int	ft_cd(char *input, char **env)
{
	int		env_sts;
	int		log;
	char	**mng_input;
	
	mng_input = ft_split(input, ' ');
	if (!mng_input || !mng_input[0])
		return (-1);
	if (!strcmp(input, "cd"))
	{
		log = go_home(env);
		return (free_splited(&mng_input), log);
	}
}