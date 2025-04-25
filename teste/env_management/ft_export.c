/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:08:04 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/24 21:22:08 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	**env_create(char **env, char **mng_input);

int ft_export(char *input, char ***env)
{
	int env_sts;
	char **mng_input;
	
	mng_input = ft_split(input, ' ');
	if (!mng_input || !mng_input[0])
		return (1);
	if (!strcmp(input, "export"))
	{
		print_in_order(*env);
		free_splited(&mng_input);
		return (0);
	}
	env_sts = env_searcher(mng_input[1], *env);
	if (env_sts != -1)
		env_update(env, mng_input, env_sts);
	else
		*env = env_create(*env, mng_input);
	free_splited(&mng_input);
	int_env_file(*env);
	return (0);
}