/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 02:32:19 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/23 02:33:06 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

static char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	v;
	char			*c_s;
	unsigned int	size;

	if (!*s || !s)
		return (calloc(1, 1));
	size = 0;
	while (s[size])
		size++;
	if (size <= start || len == 0)
		return (calloc(1, 1));
	if ((len + start) >= size)
		v = (size - start);
	else
		v = len;
	c_s = (char *)malloc((v + 1) * sizeof(char));
	if (c_s == NULL)
		return (NULL);
	c_s[v] = '\0';
	while (v--)
		c_s[v] = s[start + v];
	return ((char *)c_s);
}

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