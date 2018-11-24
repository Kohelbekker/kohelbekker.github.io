/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 19:11:23 by aperesad          #+#    #+#             */
/*   Updated: 2018/01/05 19:11:25 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (s1[k])
		k++;
	while (s2[i])
	{
		s1[k] = s2[i];
		k++;
		i++;
	}
	s1[k] = '\0';
	return (s1);
}
