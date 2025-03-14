/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalaibb <msalaibb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 14:40:30 by msalaibb          #+#    #+#             */
/*   Updated: 2024/10/14 15:08:09 by msalaibb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
		if ((char)c == *s++)
			return ((char *)--s);
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}
