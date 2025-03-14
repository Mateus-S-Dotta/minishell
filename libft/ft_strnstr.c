/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalaibb <msalaibb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:25:40 by msalaibb          #+#    #+#             */
/*   Updated: 2024/10/26 13:48:01 by msalaibb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i_b;
	size_t	i_l;

	if (*little == '\0')
		return ((char *)big);
	if (len == 0)
		return (NULL);
	i_b = 0;
	while (big[i_b] && i_b < len)
	{
		i_l = 0;
		while (big[i_b + i_l] && little[i_l] && (i_b + i_l) < len
			&& big[i_b + i_l] == little[i_l])
			i_l++;
		if (!little[i_l])
			return ((char *)&big[i_b]);
		i_b++;
	}
	return (NULL);
}
