/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:17:42 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/23 16:20:51 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_bubble_sort(char **combined, int count)
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
			if (ft_strcmp(combined[j], combined[j + 1]) > 0)
			{
				tmp = combined[j];
				combined[j] = combined[j + 1];
				combined[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	ft_print_sorted(char **combined, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		printf("declare -x %s\n", combined[i]);
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

void	print_in_order(char **env, char **env_n)
{
	int		count1;
	int		count2;
	int		i;
	int		index;
	char	**combined;

	count1 = ft_count_elems(env);
	count2 = ft_count_elems(env_n);
	combined = (char **)malloc(sizeof(char *) * (count1 + count2 + 1));
	if (!combined)
		return ;
	index = 0;
	i = 0;
	while (env[i] != NULL)
		combined[index++] = env[i++];
	i = 0;
	while (env_n[i] != NULL)
		combined[index++] = env_n[i++];
	combined[index] = NULL;
	ft_bubble_sort(combined, count1 + count2);
	ft_print_sorted(combined, count1 + count2);
	free(combined);
}
