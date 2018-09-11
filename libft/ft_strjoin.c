/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 18:29:31 by aperesad          #+#    #+#             */
/*   Updated: 2017/11/14 18:30:10 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s, char const *s2)
{
	char	*str;

	if (s == NULL || s2 == NULL)
		return (NULL);
	str = ft_strnew(ft_strlen(s) + ft_strlen(s2));
	if (str == NULL)
		return (NULL);
	ft_strcpy(str, s);
	ft_strcat(str, s2);
	return (str);
}
