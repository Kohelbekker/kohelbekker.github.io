/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_make_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 18:03:05 by aperesad          #+#    #+#             */
/*   Updated: 2018/07/02 18:03:08 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mlx			*clean_mlx(t_mlx *mlx)
{
	if (mlx->win_p != NULL)
		mlx_destroy_window(mlx->mlx_p, mlx->win_p);
	free(mlx);
	return (NULL);
}

t_mlx			*mlx_make(char *av, t_map *map)
{
	t_mlx	*mlx;

	if (!(mlx = (t_mlx *)malloc(sizeof(t_mlx))))
		return (NULL);
	if (!(mlx->mlx_p = mlx_init()) ||
		!(mlx->win_p = mlx_new_window(mlx->mlx_p, W_WID, W_HGHT, av)))
		error("ERROR: malloc error");
	mlx->map = map;
	return (mlx);
}

t_map			*scale(t_map *m)
{
	double		i;
	double		j;
	double		a;

	j = ((m->width < m->height) ? m->height : m->width);
	a = (j == m->width) ? W_HGHT : W_WID;
	i = (a - 800) / (j * DIST);
	m->scale = i;
	m->cam_x = 0.0;
	m->cam_y = 0.0;
	return (m);
}

t_map			*find_z(t_map *m, int x, int y)
{
	int			min_z;
	int			max_z;
	int			a;

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
	return (m);
}

void			make_points(char *tmp, int l, t_map *map)
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
	j = 0;
	while ((str[j] != 0) && j < map->width)
	{
		array = (t_points*)malloc(sizeof(t_points));
		array->x = j * DIST;
		array->y = l * DIST;
		array->z = ft_atoi(str[j]) * DIST_Z;
		array->h = array->z;
		map->points[l][j] = *array;
		free(array);
		ft_memdel((void **)&str[j]);
		j++;
	}
	free(str);
	ft_memdel((void **)&tmp);
}
