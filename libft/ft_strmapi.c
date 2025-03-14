/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalaibb <msalaibb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:56:03 by msalaibb          #+#    #+#             */
/*   Updated: 2024/10/21 18:07:01 by msalaibb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*s_c;

	if (!s)
		return (NULL);
	s_c = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (s_c == NULL)
		return (NULL);
	i = -1;
	while (s[++i])
		s_c[i] = f(i, s[i]);
	s_c[i] = '\0';
	return (s_c);
}
