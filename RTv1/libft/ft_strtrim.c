/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 19:00:16 by aperesad          #+#    #+#             */
/*   Updated: 2017/11/14 19:00:50 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		i;
	int		j;
	int		k;
	char	*str;

	i = 0;
	k = 0;
	if (s == NULL)
		return (NULL);
	j = ft_strlen(s) - 1;
	while (SPACE(s[i]) && s[i] != '\0')
		i++;
	while (SPACE(s[j]) && i < j)
		j--;
	if ((str = ft_strnew(j - i + 1)) == NULL)
		return (NULL);
	while (i <= j)
	{
		str[k] = s[i];
		k++;
		i++;
	}
	return (str);
}
