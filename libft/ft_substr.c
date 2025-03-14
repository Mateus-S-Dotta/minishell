/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalaibb <msalaibb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:39:50 by msalaibb          #+#    #+#             */
/*   Updated: 2024/10/17 17:33:39 by msalaibb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	v;
	char			*c_s;
	unsigned int	size;

	if (!*s || !s)
		return (ft_calloc(1, 1));
	size = 0;
	while (s[size])
		size++;
	if (size <= start || len == 0)
		return (ft_calloc(1, 1));
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
