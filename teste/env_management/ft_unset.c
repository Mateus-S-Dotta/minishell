/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:01:43 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/24 21:43:39 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_unset(char *input, char **env)
{
	int env_sts;
	char **mng_input;
	
	mng_input = ft_split(input, ' '); //unset KEY
	if (!mng_input || !mng_input[0])
		return (-1);
	if (!strcmp(input, "unset"))
	{
		free_splited(&mng_input);
		return (free_splited(&mng_input), 0);
	}
	env_sts = env_searcher(mng_input[1], env);
	if (env_sts != -1)
		env_delete(&env, env_sts);
	return (0);
}	