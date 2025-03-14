/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalaibb <msalaibb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:54:57 by msalaibb          #+#    #+#             */
/*   Updated: 2024/10/17 16:59:43 by msalaibb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest_str, const void *src_str, size_t numBytes)
{
	char	*c_d;
	char	*c_s;

	if (!dest_str && !src_str)
		return (NULL);
	c_d = (char *)dest_str;
	c_s = (char *)src_str;
	if (c_s < c_d && c_d < (c_s + numBytes))
	{
		c_s += numBytes;
		c_d += numBytes;
		while (numBytes--)
			*(--c_d) = *(--c_s);
	}
	else
		while (numBytes--)
			*c_d++ = *c_s++;
	return (dest_str);
}
