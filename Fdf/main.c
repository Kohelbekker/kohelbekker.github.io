/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 17:47:31 by aperesad          #+#    #+#             */
/*   Updated: 2018/07/02 17:47:37 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			error(char *str)
{
	ft_putendl(str);
	exit(1);
	return (0);
}

int			lines_nb(char *av, t_map **map, int lines)
{
	char	tmp;
	int		fd;

	fd = 0;
	if ((fd = open(av, O_RDONLY)) < 0)
		error("ERROR: can not open the file!");
	if (read(fd, &tmp, 1) == -1)
		error("NOT A FILE!");
	while (read(fd, &tmp, 1))
		lines = ((tmp == '\n') ? (lines + 1) : lines);
	close(fd);
	(*map)->height = lines;
	return (0);
}

int			first_line_width(char *tmp)
{
	int		j;
	char	**str;

	j = 0;
	str = ft_strsplit(tmp, ' ');
	while (str[j])
	{
		ft_memdel((void **)&str[j]);
		j++;
	}
	free(str);
	return (j);
}

t_map		*validate(char **av, int fd, int j)
{
	char	*tmp;
	t_map	*map;

	if (!(map = (t_map*)malloc(sizeof(t_map))))
		error("ERROR: malloc error");
	lines_nb(av[1], &map, 0);
	if (!(map->points = (t_points**)malloc(sizeof(t_points*) * map->height)))
		error("ERROR: malloc error");
	while (get_next_line(fd, &tmp) > 0)
	{
		if (j == 0 && (map->width = first_line_width(tmp)) < 1)
			error("ERROR: no first line");
		if (!(map->points[j] = (t_points*)malloc(sizeof(t_points) *
			map->width)))
			error("ERROR: malloc error");
		make_points(tmp, j, map);
		j++;
	}
	close(fd);
	map->height = j;
	map = scale(map);
	map = find_z(map, 0, 0);
	return (map);
}

int			main(int ac, char **av)
{
	int		fd;
	t_mlx	*mlx;
	t_map	*map;

	fd = 0;
	if (ac != 2)
		error("usage: ./fdf [map], should be one file for reading");
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		error("ERROR: ivalid input file!");
	map = validate(av, fd, 0);
	mlx = mlx_make(av[1], map);
	ft_draw(mlx);
	mlx_string_put(mlx->mlx_p, mlx->win_p, 10, 10, 0xbd59ed, " FDF proj\
		ect. Author: aperesad");
	mlx_hook(mlx->win_p, 2, 5, hooks, mlx);
	mlx_key_hook(mlx->win_p, hook_pointsonly, mlx);
	mlx_loop(mlx->mlx_p);
	return (0);
}
