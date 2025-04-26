/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:08:04 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/25 15:03:58 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	**env_create(char **env, char **mng_input);

static int	check_input(char *str)
{
	int		i;

	i = -1;
	while (str[++i] == ' ' || str[i] == '\t')
		continue ;
	return (ft_isalpha(str[i]));
}

int	ft_export(char *input, char ***env)
{
	int		env_sts;
	char	*i_hate_norm;
	char	**mng_input;

	mng_input = ft_split(input, ' ');
	i_hate_norm = ": not a valid identifier\n";
	if (!mng_input || !mng_input[0])
		return (1);
	if (!strcmp(input, "export"))
		return (print_in_order(*env), free_splited(&mng_input), 0);
	if (!check_input(mng_input[1]))
	{
		printf("minishell: export: `%s`%s", mng_input[1], i_hate_norm);
		return (free_splited(&mng_input), 1);
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
