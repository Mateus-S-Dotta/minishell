/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalaibb <msalaibb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:27:09 by msalaibb          #+#    #+#             */
/*   Updated: 2025/03/08 15:19:29 by msalaibb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_null_all(char **a, int aux)
{
	int	i;

	i = 0;
	while (i <= aux)
	{
		free(a[i]);
		i++;
	}
	free(a);
	a = NULL;
}

static int	ft_to_find_chars(char const *s, char c)
{
	int	i;
	int	n;
	int	cont;

	i = -1;
	n = 0;
	cont = 1;
	while (s[++i])
	{
		if (s[i] != c && cont)
		{
			n++;
			cont = 0;
		}
		else if (s[i] == c)
			cont = 1;
	}
	return (n);
}

static void	ft_complete_array(const char *s, char c, char **a, int aux)
{
	int	i;
	int	l;

	i = -1;
	l = 0;
	while (s[++i])
	{
		if (s[i] != c)
			l++;
		else if (l > 0 && s[i] == c)
		{
			a[aux] = ft_substr(s, i - l, l);
			if (a[aux++] == NULL)
				return (ft_null_all(a, aux));
			l = 0;
		}
	}
	if (l > 0)
	{
		a[aux] = ft_substr(s, i - l, l);
		if (a[aux++] == NULL)
			return (ft_null_all(a, aux));
	}
	a[aux] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**a;
	int		aux;

	if (s == NULL)
		return (NULL);
	aux = 0;
	a = (char **)malloc((ft_to_find_chars(s, c) + 1) * sizeof(char *));
	if (a == NULL)
		return (NULL);
	ft_complete_array(s, c, a, aux);
	return (a);
}
