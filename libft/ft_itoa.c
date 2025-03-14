/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalaibb <msalaibb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:39:58 by msalaibb          #+#    #+#             */
/*   Updated: 2024/10/21 16:36:29 by msalaibb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_know_algarism(int n)
{
	int	d;
	int	c;

	c = 0;
	d = 1;
	while (n / d <= -10)
		d *= 10;
	while (d > 0)
	{
		d = d / 10;
		c++;
	}
	return (c);
}

static char	*ft_case_0(void)
{
	char	*s;

	s = (char *)malloc(2 * sizeof(char));
	if (s == NULL)
		return (NULL);
	s[0] = '0';
	s[1] = '\0';
	return (s);
}

char	*ft_itoa(int n)
{
	int		neg;
	int		c;
	char	*s;

	if (n == 0)
		return (ft_case_0());
	neg = 1;
	if (n > 0)
	{
		neg = 0;
		n *= -1;
	}
	c = ft_know_algarism(n);
	s = (char *)malloc((c + neg + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	s[c-- + neg] = '\0';
	if (neg == 1)
		s[0] = '-';
	while (n != 0)
	{
		s[c-- + neg] = (char)('0' + (n % 10) * -1);
		n /= 10;
	}
	return (s);
}
