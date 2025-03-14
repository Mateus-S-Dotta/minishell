/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalaibb <msalaibb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:23:37 by msalaibb          #+#    #+#             */
/*   Updated: 2024/10/17 17:00:20 by msalaibb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest_str, const void *src_str, size_t n)
{
	unsigned char	*c_d;
	unsigned char	*c_s;

	if (!dest_str && !src_str)
		return (NULL);
	c_d = (unsigned char *)dest_str;
	c_s = (unsigned char *)src_str;
	while (n--)
		*c_d++ = *c_s++;
	return (dest_str);
}
