/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 20:10:06 by aperesad          #+#    #+#             */
/*   Updated: 2018/10/24 20:10:08 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		basic_check(char *av, t_wolf *w, int i)
{
	char	tmp;
	int		fd;

	if ((fd = open(av, O_RDONLY)) < 0 || (read(fd, &tmp, 0) == -1))
		error("ERROR: Can not open this file");
	while (read(fd, &tmp, 1))
	{
		if ((tmp < 48 || tmp > 50) && SPC(tmp))
			error("Wrong symbols. Use 1 to choose start position, and 0,2-4"
				"to choose textures");
		if (tmp >= 48 && tmp <= 50)
			(w->map->h == 0) ? (w->map->w++) : (i++);
		if (tmp == '\n')
		{
			if (w->map->h != 0 && i != w->map->w)
				error("Bad line length or empty lines");
			i = 0;
			w->map->h++;
		}
	}
	if (i != 0)
		w->map->h++;
	if (i != 0 && i != w->map->w)
		error("Bad line length, don't use empty lines, please");
	close(fd);
}

void		make_map(char *av, t_wolf *w, int i, int j)
{
	int		fd;
	char	*tmp;
	int		c;
	char	d;

	fd = open(av, O_RDONLY);
	w->map->map = (int **)malloc(sizeof(int *) * w->map->h);
	while (get_next_line(fd, &tmp) > 0)
	{
		j = -1;
		c = -1;
		if (!(w->map->map[++i] = (int *)malloc(sizeof(int) * w->map->w)))
			error("Malloc error");
		while (tmp[++c])
		{
			while (!SPC(tmp[c]))
				c++;
			d = tmp[c];
			w->map->map[i][++j] = ft_atoi(&d);
			if ((i == 0 || i == (w->map->h - 1) ||
				j == 0 || j == (w->map->w - 1)) && tmp[c] != '2')
				error1("map error, bad frame values", w);
		}
		free(tmp);
	}
}

void		start_position(t_wolf *w, int a, int i)
{
	int		j;

	while (i < w->map->h)
	{
		j = 0;
		while (j < w->map->w)
		{
			if (w->map->map[i][j] == 1)
			{
				if (a == 0)
				{
					w->start_x = (double)i + 0.5;
					w->start_y = (double)j + 0.5;
				}
				w->map->map[i][j] = 0;
				a++;
			}
			j++;
		}
		i++;
	}
	if (a != 1)
		error1("Please choose start position with ONLY ONE number 1"
			"on the map", w);
}

int			check_map(char *av, t_wolf *w)
{
	w->map->h = 0;
	w->map->w = 0;
	basic_check(av, w, 0);
	if (w->map->h < 3 || w->map->w < 3)
		error("Map error! You can use only digits 0,1,2. Map should be"
			"rectangular, with minimal height and width equal to 3.");
	make_map(av, w, -1, 0);
	start_position(w, 0, 0);
	w->tmp_startx = w->start_x;
	w->tmp_starty = w->start_y;
	return (0);
}
