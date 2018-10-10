#include <math.h>

#include "mlx.h"

#include <stdlib.h>
/*
g++ *.cpp -lSDL -O3 -W -Wall -ansi -pedantic
g++ *.cpp -lSDL
*/

//place the example code below here:

typedef struct    s_mlx
{
	void		*mlx_p;
	void		*win_p;
	void		*img;
	char      *data;
	int       bpp;
	int       sl;
	int       endian;
	int       color;
}       		  t_mlx;

#define mapWidth 24
#define mapHeight 24

t_mlx		*mlx_clean(t_mlx *mlx)
{
	if (mlx->win_p != NULL)
		mlx_destroy_window(mlx->mlx_p, mlx->win_p);
	if (mlx->img != NULL)
		mlx_destroy_image(mlx->mlx_p, mlx->img);
	free(mlx);
	return (0);
}

int			hooks(int key, t_mlx *mlx)
{
	if (key == 53)
	{
		mlx_clean(mlx);
		exit(0);
	}
	return (0);
}

void			my_pixel_put_to_image(char *data, int x, int y, int color, t_mlx *mlx)
{
	data[y * mlx->sl + x * mlx->bpp / 8] = color;
	data[y * mlx->sl + x * mlx->bpp / 8 + 1] = color;
	data[y * mlx->sl + x * mlx->bpp / 8 + 2] = color;
}

int worldMap[mapWidth][mapHeight]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int main(void)
{
	t_mlx  *mlx;

	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	mlx->mlx_p = mlx_init();
	double posX = 22, posY = 12;  //x and y start position
	double dirX = -1, dirY = 0; //initial direction vector
	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

	mlx->img = mlx_new_image(mlx->mlx_p, 600, 600);
	mlx->data = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->sl, &mlx->endian);
	mlx->win_p = mlx_new_window(mlx->mlx_p, 600, 600, "Ololo");
	for(int x = 0; x < 600; x++)
	{
		//calculate ray position and direction
		double cameraX = 2.0 * x / ((double)600.0) - 1; //x-coordinate in camera space
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;
		//which box of the map we're in
		int mapX = (int)posX;
		int mapY = (int)posY;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		 //length of ray from one x or y-side to next x or y-side
		double deltaDistX = fabs(1.0 / rayDirX);
		double deltaDistY = fabs(1.0 / rayDirY);
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
			 sideDistY += deltaDistY;
			 mapY += stepY;
			 side = 1;
			}
			//Check if ray has hit a wall
			if (worldMap[mapX][mapY] > 0)
			hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if (side == 0)
			perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(600 / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + 600 / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + 600 / 2;
		if (drawEnd >= 600)
			drawEnd = 600 - 1;

		//choose wall color
		if (worldMap[mapX][mapY] == 1)
			mlx->color = 0xff0000;
		else if (worldMap[mapX][mapY] == 2)
			mlx->color = 0x178c05;
		else if (worldMap[mapX][mapY] == 3)
			mlx->color = 0x0055ff;
		else if (worldMap[mapX][mapY] == 4)
			mlx->color = 0xffffff;
		else
			mlx->color = 0xffff00;

		//give x and y sides different brightness
		if (side == 1)
			mlx->color /= 2;

		//draw the pixels of the stripe as a vertical line
		while (drawStart <= drawEnd)
		{	
			my_pixel_put_to_image(mlx->data, x, drawStart, mlx->color, mlx);
			drawStart++;
	 	}
	}
	
	mlx_hook(mlx->win_p, 2, 5, hooks, mlx);
	mlx_put_image_to_window(mlx->mlx_p, mlx->win_p, mlx->img, 0, 0);
	mlx_loop(mlx->mlx_p);
	return (0);
	}
