#include "fdf.h"
#include <stdio.h>
int		hook_keydown(int key, t_mlx *mlx)
{
	(void)mlx;
	if (key == 53)
	{
		clean_mlx(mlx);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int			check_window_frame(t_mlx *mlx, t_points a)
{
	if (a.x + 1 < 0 || a.x + 1 > W_WID || a.y + 1 < 0 || a.y + 1 > W_HGHT)
		return (1);
	return (0);
}

t_mlx		*clean_mlx(t_mlx *mlx)
{
	if (mlx->win_p != NULL)
		mlx_destroy_window(mlx->mlx_p, mlx->win_p);
	if (mlx->img != NULL)
		mlx_destroy_image(mlx->mlx_p, mlx->img);
	ft_memdel((void **)&mlx);
	return (NULL);
}

t_mlx		*mlx_make(char *av, t_map *map)
{
	t_mlx	*mlx;

	if ((mlx = (t_mlx *)malloc(sizeof(t_mlx))) == NULL)
		return (NULL);
	if ((mlx->mlx_p = mlx_init()) == NULL ||
		(mlx->win_p = mlx_new_window(mlx->mlx_p, W_WID,
			W_HGHT, av)) == NULL)
		return (clean_mlx(mlx));
	if ((mlx->img = mlx_new_image(mlx->mlx_p, W_WID, W_HGHT)) == NULL)
		return (clean_mlx(mlx));
	mlx->data = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->sline,
			&mlx->endian);
	mlx->map = map;
	return (mlx);
}

void		ft_draw(t_mlx *mlx)
{
	int			x;
	int			y;
	t_points	a;
	t_points	b;

	y = 0;
	while(y < mlx->map->height)
	{
		x = 0;
		while (x < mlx->map->width)
		{
			a = mlx->map->points[y][x];
			b = mlx->map->points[y][x + 1];
			if (x + 1 < mlx->map->width)
				points(center(a, mlx), center(b, mlx), mlx);
			if (y + 1 < mlx->map->height)           //Dangerous if
					points(center(a, mlx), center(mlx->map->points[y + 1][x], mlx), mlx);
			x++;
		}
		y++;
	}
}

void		points(t_points a1, t_points a2, t_mlx *mlx)
{
	t_brez		b;
	int			color;
	int			i;

	b.dy = fabs(a2.y - a1.y);
	b.dx = fabs(a2.x - a1.x);
	b.sig_y = a1.x > a2.x ? -1 : 1;
	b.sig_x = a1.y > a2.y ? -1 : 1;
	b.err = b.dx - b.dy;
	while (a1.x != a2.x || a1.y != a2.y)
	{
		if ((i = check_window_frame(mlx, a1)) == 1)
			return ;
		if (a1.x == a2.x || a1.y == a2.y)
			(a1.x == a2.x) ? (b.sig_x = 0) : (b.sig_y = 0);
		mlx_pixel_put(mlx->mlx_p, mlx->win_p, a1.x, a1.y, /*get_color()*/0xc0dde8);
		b.err2 = b.err * 2;
		if (b.err2 > -b.dy)
		{
			b.err -= b.dy;
			a1.x += b.sig_x; 
		}
		b.err += b.dx;
		a1.y += b.sig_y;
	}
}
/////////////////////////////////////////////////////////////////////////
