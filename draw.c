#include "fdf.h"
#include <stdio.h>
typedef struct	s_a
{
	void	*mlx_p;
	void	*win_p;
}			t_a;

int exit_x(void *par)
{
par = NULL;
exit(1);
return (0);
}

int		ft_draw(t_mlx *mlx)
{
	mlx->mlx_p = mlx_init();
	mlx->win_p = mlx_new_window(mlx->mlx_p, 1000, 1000, "mlx 42");
	int x,y;
	
	x = 0;
	y = 0;

	while (y < mlx->map->height)
	{
		while (x < mlx->map->width)
		{
			//printf("line#%d, element#%d,  width=%d, height = %d, VALUE_X=%f, VALUE_Y=%f\n", y, x, mlx->map->width, mlx->map->height, mlx->map->points[y][x].x, mlx->map->points[y][x].y);
			//draw_l(150 + mlx->map->points[y][x].x, 150 + mlx->map->points[y][x].y, 150 + mlx->map->points[y][x + 1].x, 150 + mlx->map->points[y][x + 1].y, mlx);
			mlx_pixel_put(mlx->mlx_p, mlx->win_p, 150+ mlx->map->points[y][x].x, 150+ mlx->map->points[y][x].y, 0xFFFFFF);
			x++;
		}
		y++;
		x = 0;
	}
	//mlx_pixel_put(mlx->mlx_p, mlx->win_p, x, y, 0xFFFFFF);
	mlx_hook(mlx->win_p, 17, 1L << 17, exit_x, mlx);
	mlx_loop(mlx->mlx_p);
	return(0);
}