#include "fdf.h"
#include <stdio.h>

int		error(char *str)
{
	ft_putendl(str);
	exit(1);
	return (0);
}

int		make_points(char *tmp, int l, t_points ***points, int width)
{
	int			j;
	char		**str;
	t_points	*array;

	j = -1;
	str = ft_strsplit(tmp, ' ');
	while (str[j++])
		j += ft_strlen(str[j]);
	if (!((*points) = (t_points**)malloc(sizeof(t_points) * j)))
		error("ERROR: malloc error");
	j = 0;
	while (str[j])
	{
		array = (t_points*)malloc(sizeof(t_points));
		array->x = j * 20;
		array->y = l * 20;
		array->z = ft_atoi(str[j]);
		array->color = ft_atoi(str[j]);
		(*points)[j] = array;
		j++;
	}
	return(0);
}

int		lines_n_chars(int fd, t_map **map, int chrs, int lines, int f_line)
{
	char	tmp;

	while (read(fd, &tmp, 1))
	{
		if (tmp == '\n')
			chrs = (lines++, 0);
		if (tmp != '\n' && !SPACE(tmp))
			chrs++;
		if (lines == 0)
			f_line = chrs;
		if (lines != 0 && chrs > f_line)
			error("Found wrong line length. Exiting.");
		if (!SPACE(tmp) && !ft_isdigit(tmp))
		 	ft_putendl("ATTENTION: non-digit form in map!");
	}
	(*map)->width = f_line;
	(*map)->height = lines;
	return(0);
}

t_map	*validate(int fd)
{
	int			j;
	char		*tmp;
	t_map		*map;
	t_points	**tmp_p;
	
	j = 0;
	if (!(map = (t_map*)malloc(sizeof(t_map))))
		error("ERROR: malloc error");
	lines_n_chars(fd, &map, 0, 0, 0);
	if ((!(map->points = (t_points**)malloc(sizeof(t_points*) * map->height))) || 
		(map->width == 0 || map->height == 0))
		error("ERRROR!");
	while((get_next_line(fd, &tmp)) > 0)
	{
		if (!(map->points[j] = (t_points*)malloc(map->width * sizeof(t_points))))
			error("ERROR: malloc error");
		make_points(tmp, j, &tmp_p, map->width);
		map->points[j] = *tmp_p;
		j++;
	}
	return(map);
}

int		main(int ac, char **av)
{
	int		fd; 
	t_mlx	*mlx;
	t_map	*map;

	if (ac == 2)
	{
		if (!(mlx = (t_mlx*)malloc(sizeof(t_mlx))))
			error("ERROR: malloc error");
		fd = open(av[1], O_RDONLY);
		if (fd < 0)
			error("ERROR: ivalid input file!");
		map = validate(fd);
		printf("w = %d\n", map->width);
		printf("h = %d\n", map->height);
	}
	else
		error("usage: ./fdf [map], could be one file for reading");
}