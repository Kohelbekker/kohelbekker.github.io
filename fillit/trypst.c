/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trypst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 10:41:12 by aperesad          #+#    #+#             */
/*   Updated: 2017/12/11 10:41:22 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		trypst_lft(char *s, char *map, int l, int f)
{
	int		y;

	if (map[f] != '.')
		return (0);
	y = 1;
	if (s[l - 1] == '#' && map[f - 1] == '.')
		y += trypst_lft(s, map, l - 1, f - 1);
	if (s[l + 5] == '#' && map[f + map[1] + 1] == '.' &&
		s[(((l - (l / 21)) / 5) * 5 + (l / 21)) + 5] != '\n')
		y += trypst2(s, map, l + 5, f + map[1] + 1);
	return (y);
}

int		trypst_rght(char *s, char *map, int l, int f)
{
	int		y;

	if (map[f] != '.')
		return (0);
	y = 1;
	if (s[l + 1] == '#' && map[f + 1] == '.')
		y += trypst_rght(s, map, l + 1, f + 1);
	if (s[l + 5] == '#' && map[f + map[1] + 1] == '.' &&
		s[(((l - (l / 21)) / 5) * 5 + (l / 21)) + 5] != '\n')
		y += trypst2(s, map, l + 5, f + map[1] + 1);
	return (y);
}

int		trypst2(char *s, char *map, int l, int f)
{
	int		y;

	if (map[f] != '.')
		return (0);
	y = 1;
	if (s[l] == '#' && s[l + 1] == '#' && s[l + 5] == '#' && s[l + 6] == '#' &&
		s[(((l - (l / 21)) / 5) * 5 + (l / 21)) + 5] != '\n' && map[f] == '.' &&
		map[f + 1] == '.' && map[f + map[1] + 1] == '.' &&
		map[f + map[1] + 2] == '.')
		return (4);
	else
	{
		if (s[l + 1] == '#' && map[f + 1] == '.')
			y += trypst_rght(s, map, l + 1, f + 1);
		if (s[l - 1] == '#' && map[f - 1] == '.')
			y += trypst_lft(s, map, l - 1, f - 1);
		if (s[l + 5] == '#' && map[f + map[1] + 1] == '.' &&
			s[(((l - (l / 21)) / 5) * 5 + (l / 21)) + 5] != '\n')
			y += trypst2(s, map, l + 5, f + map[1] + 1);
	}
	return (y);
}

char	*trypst(char *s, char *map, int f, int j)
{
	int		l;

	l = 21 * j;
	if (!s[l] || (s[l - 1] == '\0' && l > 5))
		end(map);
	if (s[l])
	{
		while (s[l] != '#')
			l++;
		while (trypst2(s, map, l, f) != 4 && map[f])
			if (map[++f] == '\n')
				f++;
		if (map[f])
		{
			pst(s, map, l, f);
			if (map[0]++ && !(trypst(s, map, 2, j + 1)))
			{
				freemap(map, --map[0]);
				if (!(trypst(s, map, f + 1, j)))
					return (NULL);
			}
			return (map);
		}
	}
	return (NULL);
}
