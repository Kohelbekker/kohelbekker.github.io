/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:26:31 by aperesad          #+#    #+#             */
/*   Updated: 2017/11/07 16:27:49 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str1, const char *str2)
{
	int i;
	int j;
	int n;

	i = 0;
	n = ft_strlen(str2);
	if (n == 0 || str2 == str1)
		return ((char *)str1);
	while (str1[i] != '\0')
	{
		j = 0;
		while (str2[j] == str1[i + j])
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
