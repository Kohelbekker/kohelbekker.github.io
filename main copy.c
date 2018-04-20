#include "fdf.h"
#include <stdio.h>

int		error(char *str)
{
	ft_putendl(str);
	exit(1);
	return (0);
}

int		first_line_width(char *tmp)
{
	int		j;
	char	**str;

	j = 0;
	str = ft_strsplit(tmp, ' ');
	while (str[j])
		j++;
	return (j);
}

int		make_points(char *tmp, int l, t_points ***points, t_map *map)
{
	int			j;
	char		**str;
	t_points	*array;

	j = 0;
	str = ft_strsplit(tmp, ' ');
	while (str[j])
		j++;
	if (j < map->width)
		error("Bad line length in map");
	if (!((*points) = (t_points**)malloc(sizeof(t_points) * (j))))
		error("ERROR: malloc error");
	j = 0;
	while (str[j] &&  j < map->width)
	{
		array = (t_points*)malloc(sizeof(t_points));
		array->x = j * 30;
		array->y = l * 30;
		array->z = ft_atoi(str[j]);
		array->color = ft_atoi(str[j]);
		(*points)[j] = array;
		j++;
	}
	printf("|||y0 = %f\n|||", (*points)[8]->);
	return (0);
}

int		lines_nb(char *av, t_map **map, int lines)
{
	char	tmp;
	int fd = 0;
	
	if ((fd = open(av, O_RDONLY)) < 0)
		error("ERROR: can not opet the file!");
	while (read(fd, &tmp, 1))
	{
		if (tmp == '\n')
			lines++;
		if (!SPACE(tmp) && !ft_isdigit(tmp))
		 	ft_putendl("ATTENTION: non-digit form in map!");
	}
	close(fd);
	(*map)->height = lines;
	return(0);
}

t_map	*validate(char **av, int fd)
{
	int			j;
	char		*tmp;
	t_map		*map;
	t_points	**tmp_p;

	j = 0;
	if (!(map = (t_map*)malloc(sizeof(t_map))))
		error("ERROR: malloc error");
	lines_nb(av[1], &map, 0);
	if ((!(map->points = (t_points**)malloc(sizeof(t_points*) * map->height))) 
		|| map->height == 0)
		error("ERRROR!");
	while((get_next_line(fd, &tmp)) > 0)
	{
		//printf("%s\n", tmp);
		if (j == 0 && (map->width = first_line_width(tmp)) < 1)
			error("ERROR: no first line");
		if (!(map->points[j] = (t_points*)malloc(sizeof(t_points))))
			error("ERROR: malloc error");
		make_points(tmp, j, &tmp_p, map);
		//printf("y  = %f\n", (*tmp_p)[8].x);
		map->points[j] = *tmp_p;
		//printf("y2 = %f\n", map->points[j][8].x);
		j++;
	}
	map->height = j;
	return(map);
	free(tmp);
}

int		main(int ac, char **av)
{
	int		fd; 
	t_mlx	*mlx;
	t_map	*map;

	fd = 0;
	if (ac == 2)
	{
		if (!(mlx = (t_mlx*)malloc(sizeof(t_mlx))))
			error("ERROR: malloc error");
		fd = open(av[1], O_RDONLY);
		if (fd < 0)
			error("ERROR: ivalid input file!");
		map = validate(av, fd);
		mlx->map = map;
		//printf("bad value = %f\n", map->points[1][4].x);
		ft_draw(mlx);
	}
	else
		error("usage: ./fdf [map], could be one file for reading");
	free(map);
	free(mlx);
}