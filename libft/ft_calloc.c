/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalaibb <msalaibb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 14:58:25 by msalaibb          #+#    #+#             */
/*   Updated: 2025/02/20 16:57:05 by msalaibb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*s;
	unsigned int	i;
	unsigned int	t;

	t = nmemb * size;
	i = 0;
	s = (unsigned char *)malloc(t);
	while (i < t)
		s[i++] = 0;
	return (s);
}
