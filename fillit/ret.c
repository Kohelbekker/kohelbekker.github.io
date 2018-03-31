/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ret.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 10:40:04 by aperesad          #+#    #+#             */
/*   Updated: 2017/12/11 10:40:23 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	ret(char *s, int b)
{
	write(1, s, b);
	exit(0);
}

void	end(char *map)
{
	int l;

	l = 0;
	map += 2;
	while (map[l])
		l++;
	write(1, map, l);
	exit(0);
}

void	freemap(char *map, char c)
{
	int		l;

	l = 1;
	while (map[++l])
		if (map[l] == c)
			map[l] = '.';
}

int		howmf_ret(char *s, int i, int f)
{
	if ((s[i - 2] == '\n' || s[i - 1] != '\n') || (f == 0))
		return (-1);
	return (f);
}

int		howmf(char *s, int i, int f, int o)
{
	int		t;
	int		h;

	h = 0;
	while (s[++i])
	{
		t = 0;
		while ((s[i] == '#' || s[i] == '.') && s[i])
			if (t++ > -5 && s[i++] == '#')
				o++;
		if ((s[i] != '\n' || t != 4) && s[i])
			return (-1);
		h++;
		if (s[i] == '\n' && (s[i + 1] == '\n' || s[i + 1] == '\0'))
		{
			if (s[i + 1] != '\0')
				i++;
			if (f++ > -6 && (o != 4 || h != 4))
				return (-1);
			o = 0;
			h = 0;
		}
	}
	return (howmf_ret(s, i, f));
}
