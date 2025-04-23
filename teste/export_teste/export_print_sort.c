/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print_sort.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 01:27:20 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/23 02:09:58 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

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
	int	i;

	i = 0;
	while (i < count)
	{
		printf("declare -x %s\n", env[i]);
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

void	print_in_order(char **env)
{
	int	count;

	count = ft_count_elems(env);
	ft_bubble_sort(env, count);
	ft_print_sorted(env, count);
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*c;

	i = 0;
	c = (char *)s;
	while (c[i])
		i++;
	c = (char *)malloc((i + 1) * sizeof(char));
	if (c == NULL)
		return (NULL);
	c[i] = '\0';
	while (i--)
		c[i] = s[i];
	return (c);
}
