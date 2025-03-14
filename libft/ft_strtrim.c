/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalaibb <msalaibb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:23:48 by msalaibb          #+#    #+#             */
/*   Updated: 2024/10/16 15:26:15 by msalaibb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int	s;
	int	l;

	s = 0;
	if (!s1 || !*s1)
		return (ft_calloc(1, 1));
	while (s1[s] && ft_strchr(set, s1[s]))
		s++;
	l = ft_strlen(s1);
	while (s1[l - 1] && ft_strrchr(set, s1[l - 1]))
		l--;
	return (ft_substr(s1, s, (l - s)));
}
