/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 19:07:24 by aperesad          #+#    #+#             */
/*   Updated: 2017/11/16 19:07:26 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_intlen(int n)
{
	size_t k;

	k = 1;
	while ((n = n / 10))
		k++;
	return (k);
}

char			*ft_itoa(int n)
{
	char			*str;
	unsigned int	k;
	size_t			len;

	k = n;
	len = ft_intlen(n);
	if (n < 0)
	{
		len++;
		k = -1 * n;
	}
	str = ft_strnew(len);
	if (str == NULL)
		return (NULL);
	str[--len] = k % 10 + 48;
	while ((k = k / 10))
		str[--len] = (k % 10) + 48;
	if (n < 0)
		str[0] = '-';
	return (str);
}
