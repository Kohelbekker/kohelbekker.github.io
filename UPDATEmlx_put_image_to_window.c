
#include        "fdf.h"
#include <stdio.h>
// typedef struct	s_env {
// 	void	*mlx_ptr;
// 	void	*win_ptr;
// 	void	*img_ptr;
// 	char	*data;
// 	int		bpp;
// 	int		sizeline;
// 	int		endian;
// }				t_env;

// int		hook_keydown(int key, t_mlx *mlx)
// {
// 	(void)mlx;
// 	if (key == 53)
// 	{
// 		mlx_destroy_image(mlx->mlx_p, mlx->img);
// 		mlx_destroy_window(mlx->mlx_p, mlx->win_p);
// 		exit(EXIT_SUCCESS);
// 	}
// 	return (0);
// }

void    my_pixel_put_to_image(unsigned long img_color, char *data, int sizeline, int bpp, int x, int y)
{
	int i;

	unsigned char color1;
	unsigned char color2;
	unsigned char color3;

	/*if (j < 10)
	{
		fprintf(stdout,"sizeline=%d\nbpp=%d\nimg_color=%lu\n", sizeline, bpp, img_color);
		fprintf(stdout,"[]=%d\n[+1]=%d\n[+2]=%d\n", y * sizeline + x * bpp / 8 , y * sizeline + x * bpp / 8  + 1, y * sizeline + x * bpp / 8 + 2);
		printf("%d\n", j);
	}*/
	
	color1 = (img_color & 0xFF00000) >> 24;
	color2 = (img_color & 0xFF00000) >> 16;
	color3 = (img_color & 0xFF00000) >> 16;
	/*if (j < 10)
	{
		//fprintf(stdout,"color=%d\ncolor2=%d\ncolor3=%d\n", (int)color1, (int)color2, (int)color3);
		//fprintf(stdout,"color=%d\ncolor2=%d\ncolor3=%d\n", y * sizeline + x * bpp / 8 , y * sizeline + x * bpp / 8 + 1, y * sizeline + x * bpp / 8 + 2);
		
	}*/

	data[y * sizeline + x * bpp / 8 ] = color1;
	data[y * sizeline + x * bpp / 8 + 1] = color2;
	data[y * sizeline + x * bpp / 8 + 2] = color3;
}


int		ft_draw(t_mlx *mlx)
{
	t_points a;
	int x = 0;
	int y = 0;
	mlx->img_color = mlx_get_color_value(mlx->mlx_p, 0xc0dde8);
	printf("img_color = %d", mlx->img_color);
	while (y < mlx->map->height)
		{
			while (x < mlx->map->width)
			{
				a = center(mlx->map->points[y][x], mlx); 
				my_pixel_put_to_image(mlx->img_color, mlx->data, mlx->sline, mlx->bpp, a.x, a.y);
				x++;
			}
			x = 0;
			y++;
		}
	mlx_put_image_to_window(mlx->mlx_p, mlx->win_p, mlx->img, 5, 5);
	mlx_key_hook(mlx->win_p, hook_keydown, mlx);
	mlx_loop(mlx->mlx_p);
	return(0);
}