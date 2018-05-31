#include "fdf.h"
#include <stdio.h>

t_mlx		*mlx_make(char *av, t_map *map);

int			error(char *str)
{
	ft_putendl(str);
	exit(1);
	return (0);
}

double		scale(t_map *m)
{
	double	i;
	double	j;

	j = ((m->width < m->height) ? m->height : m->width);
	i = (W_HGHT - 400) / (j * DIST);
	return (i);
}

t_points	scale_mat(t_points a, t_mlx *mlx)
{
	t_points	v;

	v.x = a.x;
	v.y = a.y;
	v.z = a.z;
	v.x *= mlx->map->scale;
	v.y *= mlx->map->scale;
	v.z *= mlx->map->scale;
	return (v);
}

t_points	angle_mat(t_points a)
{
	t_points	v;
	double		x;
	double		y;
	double		z;

	x = a.x;
	z = a.z;
	y = a.y;
	v.x = x;
	v.y = cos(0.5) * y - sin(0.5) * z;
	v.z = -sin(0.5) * y + cos(0.5) * z;
	v.color = a.color;
	return (v);
}


t_points	center(t_points a, t_mlx *mlx)
{
	a.x -= ((mlx->map->width - 1) / 2.0) * DIST;
	a.y -= ((mlx->map->height - 1) / 2.0) * DIST;
	a.z -= (double)(mlx->map->z_max + mlx->map->z_min) / 2.0;
	a = scale_mat(a, mlx); 
	a.x += W_WID / 2;
	a.y += W_HGHT / 2;
	a = angle_mat(a);
	a.x = (int)a.x;
	a.y = (int)a.y;
	a.z = (int)a.z;
	return (a);               
}


t_map		*find_z(t_map *m)
{
	int			min_z;
	int			max_z;
	int			x;
	int			y;
	int			a;

	y = 0;
	max_z = -2147483648;
	min_z = 2147483647;
	while (y < m->height)
	{
		x = 0;
		while (x < m->width)
		{
			a = m->points[y][x].z;
			if (a < min_z)
				min_z = a;
			if (a > max_z)
				max_z = a;
			x++;
		}
		y++;
	}
	m->z_min = min_z;
	m->z_max = max_z;
	return(m);
}

int			first_line_width(char *tmp)
{
	int		j;
	char	**str;

	j = 0;
	str = ft_strsplit(tmp, ' ');
	while (str[j])
		j++;
	return (j);
}

t_points	*make_points(char *tmp, int l, t_map *map)
{
	int			j;
	char		**str;
	t_points	*array;
	t_points	**points;

	j = 0;
	str = ft_strsplit(tmp, ' ');
	while (str[j])
		j++;
	if (j < map->width)
		error("Bad line length in map");
	if (!(points = (t_points**)malloc(sizeof(t_points) * (j))))
		error("ERROR: malloc error");
	j = 0;
	while (str[j] &&  j < map->width)
	{
		array = (t_points*)malloc(sizeof(t_points));
		array->x = (float)j * DIST;
		array->y = (float)l * DIST;
		array->z = (float)ft_atoi(str[j]);
		array->color = ft_atoi(str[j]);
		points[j] = array;
		j++;
	}
	return (*points);
}

int		lines_nb(char *av, t_map **map, int lines)
{
	char	tmp;
	int fd = 0;
	
	if ((fd = open(av, O_RDONLY)) < 0)
		error("ERROR: can not open the file!");
	while (read(fd, &tmp, 1))
	{
		if (tmp == '\n')
			lines++;
		if (!SPACE(tmp) && !ft_isdigit(tmp) && (tmp != '-')) 
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

	j = 0;
	if (!(map = (t_map*)malloc(sizeof(t_map))))
		error("ERROR: malloc error");
	lines_nb(av[1], &map, 0);
	if ((!(map->points = (t_points**)malloc(sizeof(t_points*) * map->height))) 
		|| map->height == 0)
		error("ERRROR!");
	while((get_next_line(fd, &tmp)) > 0)
	{
		if (j == 0 && (map->width = first_line_width(tmp)) < 1)
			error("ERROR: no first line");
		if (!(map->points[j] = (t_points*)malloc(sizeof(t_points))))
			error("ERROR: malloc error");
		map->points[j] = make_points(tmp, j, map);
		j++;
	}
	map->height = j;
	map->scale = scale(map);
	map = find_z(map);
	return(map);
}

int		main(int ac, char **av)
{
	int		fd; 
	t_mlx	*mlx;
	t_map	*map;

	fd = 0;
	if (ac != 2)
		error("usage: ./fdf [map], should be one file for reading");
	if (!(mlx = (t_mlx*)malloc(sizeof(t_mlx))))
		error("ERROR: malloc error");
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		error("ERROR: ivalid input file!");
	map = validate(av, fd);
	mlx = mlx_make(av[1], map);	
	ft_draw(mlx);
	mlx_key_hook(mlx->win_p, hook_keydown, mlx);
	mlx_loop(mlx->mlx_p);
}