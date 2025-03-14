/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalaibb <msalaibb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:23:48 by msalaibb          #+#    #+#             */
/*   Updated: 2024/10/14 13:52:12 by msalaibb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	d_l;
	size_t	s_l;
	size_t	i;

	d_l = 0;
	s_l = 0;
	while (dst[d_l] != '\0' && d_l < size)
		d_l++;
	while (src[s_l] != '\0')
		s_l++;
	if (size <= d_l)
		return (size + s_l);
	i = 0;
	while (src[i] != '\0' && d_l + 1 < size)
	{
		dst[d_l] = src[i];
		d_l++;
		i++;
	}
	dst[d_l] = '\0';
	return (d_l + s_l - i);
}
