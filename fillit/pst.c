/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 10:39:22 by aperesad          #+#    #+#             */
/*   Updated: 2017/12/11 10:39:37 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	pst_lft(char *s, char *map, int l, int f)
{
	map[f] = map[0];
	if (s[l - 1] == '#')
		pst_lft(s, map, l - 1, f - 1);
	if (s[l + 5] == '#' &&
		s[(((l - (l / 21)) / 5) * 5 + (l / 21)) + 5] != '\n')
		pst(s, map, l + 5, f + map[1] + 1);
}

void	pst_rght(char *s, char *map, int l, int f)
{
	map[f] = map[0];
	if (s[l + 1] == '#')
		pst_rght(s, map, l + 1, f + 1);
	if (s[l + 5] == '#' &&
		s[(((l - (l / 21)) / 5) * 5 + (l / 21)) + 5] != '\n')
		pst(s, map, l + 5, f + map[1] + 1);
}

void	pst(char *s, char *map, int l, int f)
{
	if (s[l] == '#' && s[l + 1] == '#' && s[l + 5] == '#' && s[l + 6] == '#' &&
		s[(((l - (l / 21)) / 5) * 5 + (l / 21)) + 5] != '\n')
	{
		map[f] = map[0];
		map[f + 1] = map[0];
		map[f + map[1] + 1] = map[0];
		map[f + map[1] + 2] = map[0];
	}
	else
	{
		map[f] = map[0];
		if (s[l + 1] == '#')
			pst_rght(s, map, l + 1, f + 1);
		if (s[l - 1] == '#')
			pst_lft(s, map, l - 1, f - 1);
		if (s[l + 5] == '#' &&
			s[(((l - (l / 21)) / 5) * 5 + (l / 21)) + 5] != '\n')
			pst(s, map, l + 5, f + map[1] + 1);
	}
}

int		check2(char *s, int i, int l)
{
	int		y;

	y = 1;
	if (i == l && s[l + 1] == '#' && s[l + 5] == '#' && s[l + 6] == '#' &&
		s[(((l - (l / 21)) / 5) * 5 + (l / 21)) + 5] != '\n')
		return (4);
	else
	{
		if (s[l + 1] == '#' && l + 1 != i)
			y += check2(s, l, l + 1);
		if (s[l - 1] == '#' && l - 1 != i)
			y += check2(s, l, l - 1);
		if (s[l + 5] == '#' && l + 5 != i &&
			s[(((l - (l / 21)) / 5) * 5 + (l / 21)) + 5] != '\n')
			y += check2(s, l, l + 5);
	}
	return (y);
}

int		check(char *s, int l)
{
	while (s[l])
	{
		while (s[l] && s[l] != '#')
			l++;
		if (check2(s, l, l) != 4)
			return (-1);
		while ((s[l] != '\n' || s[l - 1] != '\n') && s[l + 1] != '\0')
			l++;
		l++;
	}
	return (0);
}
