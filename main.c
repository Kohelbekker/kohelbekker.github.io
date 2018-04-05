#include "fdf.h"
#include <stdio.h>

int		error(char *str)
{
	ft_putendl(str);
	exit(1);
	return (0);
}

// int		choose_color()
// {
// 	return (0);
// }

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
	while (str[j] && j < width)
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

t_map		*lines_n_chars(int fd)
{
	int		chrs;
	int		lines;
	char	tmp;
	t_map	*map;


	lines = 0;
	chrs = 0;
	while (read(fd, &tmp, 1))
	{
		while (lines == 0 && tmp != '\n')
		{
			if (!SPACE(tmp))
				chrs++;
		}
		if (tmp == '\n')
			lines++;
		if (!SPACE(tmp) && !ft_isdigit(tmp))
			ft_putendl("ATTENTION: non-digit form in map!");
	}
	map->width = chrs;
	map->height = lines;
	return(map);
}

t_map	*validate(int fd, char *av)
{
	int			lines;
	int			j;
	char		*tmp;
	t_map		*map;
	t_points	**tmp_p;

	j = 0;
	if (!(map = (t_map*)malloc(sizeof(t_map))))
		error("ERROR: malloc error");
	map = lines_n_chars(fd);
	if ((!(map->points = (t_points***)malloc(sizeof(t_points**) * map->height))) || 
		(map->width == 0 || map->height == 0))
		error("ERRROR!");
	while((get_next_line(fd, &tmp)) > 0)
	{
		if (!(map->points[j] = (t_points**)malloc(map->height * sizeof(t_points*))))
			error("ERROR: malloc error");
		make_points(tmp, j, &tmp_p, map->width);
		map->points[j] = tmp_p;
		j++;
	}
	return(map);
}

int		main(int ac, char **av)
{
	int		fd; 
	t_mlx	*mlx;
	t_map	*map;
	FILE * pFile;

	pFile = fopen("text.txt", "w");
	fprintf(pFile, "Hello!");
	if (ac == 2)
	{
		if (!(mlx = (t_mlx*)malloc(sizeof(t_mlx))))
			error("ERROR: malloc error");
		fd = open(av[1], O_RDONLY);
		if (fd < 0)

			error("ERROR: ivalid input file!");
		map = validate(fd, av[1]);
	}
	else
		error("usage: ./fdf [map], could be one file for reading");
}