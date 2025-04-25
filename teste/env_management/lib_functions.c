/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:12:22 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/24 18:05:58 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

void	free_splited(char ***splited)
{
	int i;
	
	if (!*splited)
		return;
	
	i = -1;
	while ((*splited)[++i])
		free((*splited)[i]);
	
	free(*splited);
}

char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*c;

	i = 0;
	while (s[i] && i < n)
		i++;
	c = (char *)malloc((i + 1) * sizeof(char));
	if (c == NULL)
		return (NULL);
	c[i] = '\0';
	while (i--)
		c[i] = s[i];
	return (c);
}
