/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalaibb <msalaibb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:03:37 by msalaibb          #+#    #+#             */
/*   Updated: 2024/10/14 13:52:10 by msalaibb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t		s_s;
	size_t		i;

	i = 0;
	s_s = 0;
	while (src[s_s] != '\0')
		s_s++;
	if (size <= 0)
		return (s_s);
	while (--size && *src != '\0')
		*dst++ = *src++;
	*dst = '\0';
	return (s_s);
}
