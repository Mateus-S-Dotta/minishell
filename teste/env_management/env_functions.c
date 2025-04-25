/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:02:29 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/24 21:17:57 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	env_update(char ***env, char **mng_input, int i);
void	env_delete(char ***env, int i);
int		env_searcher(char *field, char **env);
char	**env_create(char **env, char **mng_input);

void env_update(char ***env, char **mng_input, int i)
{
	char *tmp_env;
	
	tmp_env = (*env)[i];
	(*env)[i] = ft_strdup(mng_input[1]);
	free(tmp_env);
}

void env_delete(char ***env, int i)
{
	char	**new_env;
	int		j = 0;
	int		k = 0;

	while ((*env)[j])
		j++;
	new_env = (char **)malloc(sizeof(char *) * j);
	if (!new_env)
		return;
	j = 0;
	while ((*env)[j])
	{
		if (j != i)
			new_env[k++] = ft_strdup((*env)[j]);
		j++;
	}
	new_env[k] = NULL;
	free_splited(env);
	*env = new_env;
}

char **env_create(char **env, char **mng_input)
{
	char **new_env;
	int i;
	
	i = -1;
	while(env[++i])
		continue;
	new_env = (char **)malloc(sizeof(char *) * (i + 2));
	i = -1;
	while(env[++i])
		new_env[i] = ft_strndup(env[i], strlen(env[i]));
	new_env[i++] = ft_strdup(mng_input[1]);
	new_env[i] = NULL;
	free_splited(&env);
	return (new_env);
}

int	env_searcher(char *field, char **env)
{
	char	**tmp_field;
	int i;
	
	if (!field || !env)
		return (-1);
	tmp_field = ft_split(field, '=');
	i = -1;
	while (env[++i])
	{
		if (!strncmp(env[i], tmp_field[0], strlen(tmp_field[0])))
			return (free_splited(&tmp_field), i);
	}
	free_splited(&tmp_field);
	return (-1);
}
