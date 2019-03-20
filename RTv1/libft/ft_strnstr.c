/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 19:31:19 by aperesad          #+#    #+#             */
/*   Updated: 2017/11/07 19:31:27 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str1, const char *str2, size_t n)
{
	size_t	i;
	size_t	j;
	int		a;

	i = 0;
	a = ft_strlen(str2);
	if (a == 0 || str2 == str1)
		return ((char *)str1);
	while (str1[i] != '\0' && i < n)
	{
		j = 0;
		while (str2[j] == str1[i + j] && (i + j) < n)
		{
			if (str2[j + 1] == '\0')
			{
				return ((char *)str1 + i);
			}
			j++;
		}
		i++;
	}
	return (0);
}
