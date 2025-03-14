/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalaibb <msalaibb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:46:10 by msalaibb          #+#    #+#             */
/*   Updated: 2024/10/15 15:18:14 by msalaibb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	size;
	unsigned int	aux;
	char			*c;

	aux = -1;
	size = 0;
	while (s1[++aux])
		size++;
	aux = -1;
	while (s2[++aux])
		size++;
	c = (char *)malloc((size + 1) * sizeof(char));
	if (!c)
		return (NULL);
	aux = -1;
	c[size] = '\0';
	while (s1[++aux])
		c[aux] = s1[aux];
	size = 0;
	while (s2[size])
		c[aux++] = s2[size++];
	return (c);
}
