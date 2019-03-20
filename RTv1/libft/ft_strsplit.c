/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 12:31:31 by aperesad          #+#    #+#             */
/*   Updated: 2017/11/18 12:32:00 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_words_nbr(char const *s, char c)
{
	int	i;
	int	nbr;

	nbr = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0' && s[i] != c)
			nbr++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (nbr);
}

static size_t	ft_nbr_lttrs(char const *s, char c)
{
	int	i;
	int	lttrs;

	i = 0;
	lttrs = 0;
	while (s[i] == c)
		i++;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
		lttrs++;
	}
	return (lttrs);
}

static char		**ft_delmem(int i, char **str)
{
	while (i > 0)
	{
		free(str[i]);
		i--;
	}
	free(str);
	return (NULL);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**str;
	size_t	i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	str = (char **)malloc(sizeof(*str) * (ft_words_nbr(s, c) + 1));
	if (str == NULL)
		return (NULL);
	while (i < ft_words_nbr(s, c))
	{
		k = 0;
		if ((str[i] = ft_strnew(ft_nbr_lttrs(&s[j], c) + 1)) == NULL)
			return (ft_delmem(i, str));
		while (s[j] == c)
			j++;
		while (s[j] != c && s[j] != '\0')
			str[i][k++] = s[j++];
		str[i++][k] = '\0';
	}
	str[i] = 0;
	return (str);
}
