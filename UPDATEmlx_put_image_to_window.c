
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

// int		hook_keydown(int key, void *win_ptr)
// {
// 	if (key == 53)
// 		exit(EXIT_SUCCESS);
// 	return (0);
// }



int		ft_draw(t_mlx *mlx)
{
	int x = 0;
	int y = 0;
	mlx->mlx_p = mlx_init();
	mlx->img = mlx_new_image(mlx->mlx_p, 1100, 1100);
	mlx->data = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->sline, &mlx->endian);
	mlx->img_color = mlx_get_color_value(mlx->mlx_p, 0xc0dde8);
	printf("height = %d, width = %d", mlx->map->height, mlx->map->width);
	while (y < mlx->map->height)
		{
			while (x < mlx->map->width)
			{
				my_pixel_put_to_image(mlx->img_color, mlx->data, mlx->sline, mlx->bpp, mlx->map->points[y][x].x, mlx->map->points[y][x].y);
	            printf("x=%f\n", mlx->map->points[y][x].x);
				x++;
			}
			x = 0;
			y++;
			printf("Y!");
		}
	mlx->win_p = mlx_new_window(mlx->mlx_p, 1200,1150, "Drew" );
	mlx_put_image_to_window(mlx->mlx_p, mlx->win_p, mlx->img, 100, 100);
	//mlx_key_hook(mwin_p, hook_keydown, (void *)0);
	mlx_loop(mlx->mlx_p);
	return(0);
}