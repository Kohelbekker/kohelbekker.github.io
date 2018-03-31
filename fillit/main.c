/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 10:38:34 by aperesad          #+#    #+#             */
/*   Updated: 2017/12/11 10:41:50 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

char	*do_map(int h)
{
	char	*map;
	int		i;
	int		o;
	int		l;

	i = 0;
	o = h;
	l = 2;
	if (!(map = malloc(sizeof(char) * (h * h) + h + 3)))
		ret("error\n", 6);
	map[0] = 'A';
	map[1] = h;
	while (o > 0)
	{
		i = -1;
		while (++i < h)
			map[l++] = '.';
		map[l++] = '\n';
		o--;
	}
	map[l] = '\0';
	return (map);
}

int		krn(int f)
{
	int		h;

	h = 2;
	while (h * h < f * 4)
		h++;
	return (h);
}

char	*str(char *s, int l)
{
	char	buff[1];
	char	*snew;
	int		b;

	if ((b = open(s, O_RDONLY)) == -1)
		ret("error\n", 6);
	while (read(b, buff, 1))
		l++;
	close(b);
	if (l < 19)
		ret("error\n", 6);
	if ((b = open(s, O_RDONLY)) == -1)
		ret("error\n", 6);
	if (!(snew = malloc(sizeof(char) * (l + 1))))
		ret("error\n", 6);
	l = 0;
	while (read(b, buff, 1))
		snew[l++] = buff[0];
	snew[l] = '\0';
	close(b);
	l = -1;
	return (snew);
}

int		main(int ac, char **av)
{
	char	*s;
	char	*map;
	char	*map2;
	int		f;

	if (ac != 2)
		ret("usage: ./fillit input_file\n", 27);
	s = str(av[1], 0);
	f = howmf(s, -1, 0, 0);
	if (f == -1 || check(s, 0) == -1)
		ret("error\n", 6);
	map2 = NULL;
	while (!map2)
	{
		map = do_map(krn(f++));
		map2 = trypst(s, map, 2, 0);
		free(map);
	}
	return (0);
}
