/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:17:42 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/25 16:03:18 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		print_in_order(char **env);
static void	ft_bubble_sort(char **env, int count);
static void	ft_print_sorted(char **env, int count);
static int	ft_count_elems(char **arr);

void	print_in_order(char **env)
{
	int	count;

	count = ft_count_elems(env);
	ft_bubble_sort(env, count);
	ft_print_sorted(env, count);
}

static void	ft_bubble_sort(char **env, int count)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (strcmp(env[j], env[j + 1]) > 0)
			{
				tmp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	ft_print_sorted(char **env, int count)
{
	int		i;
	char	*key;
	char	*value;
	char	*equal_sign;

	i = 0;
	while (i < count)
	{
		equal_sign = strchr(env[i], '=');
		if (equal_sign)
		{
			key = strndup(env[i], equal_sign - env[i]);
			value = strdup(equal_sign + 1);
			value[strlen(value) - 1] = '\0';
			printf("declare -x %s=\"%s\"\n", key, value);
			free(key);
			free(value);
		}
		else
			printf("declare -x %s", env[i]);
		i++;
	}
}

static int	ft_count_elems(char **arr)
{
	int	count;

	if (arr == NULL || *arr == NULL)
		return (0);
	count = 0;
	while (arr[count] != NULL)
		count++;
	return (count);
}
