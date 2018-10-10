#include <math.h>

#include "mlx.h"

#include <stdlib.h>

#define mapWidth 24
#define mapHeight 24

/*
g++ *.cpp -lSDL -O3 -W -Wall -ansi -pedantic
g++ *.cpp -lSDL
*/

//place the example code below here:

typedef struct    s_mlx
{
	void      *mlx_p;
	void      *win_p;
	void      *img;
	char      *data;
	int       bpp;
	int       sl;
	int       endian;
	int       color;
}         t_mlx;

typedef struct    s_wolf
{
	t_mlx	*mlx;
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	double time;
	double oldTime;
	double cameraX;
	double rayDirX;
	double rayDirY;
	int mapX;
	int mapY;
	double sideDistX;
	double sideDistY;
	double deltaDistX;
	double deltaDistY;
	double perpWallDist;
	int stepX;
	int stepY;
	int hit;
	int side;
	int lineHeight;
	int drawStart;
	int drawEnd;

}         t_wolf;

#define mapWidth 24
#define mapHeight 24

#define rotSpeed ((M_PI / 180) * 10)
#define moveSpeed ((M_PI / 180) * 12)

void	draw(t_wolf *w);

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

t_mlx		*mlx_clean(t_mlx *mlx)
{
	if (mlx->win_p != NULL)
		mlx_destroy_window(mlx->mlx_p, mlx->win_p);
	if (mlx->img != NULL)
		mlx_destroy_image(mlx->mlx_p, mlx->img);
	free(mlx);
	return (0);
}

int			hooks(int key, t_wolf *w)
{
	if (key == 53)
	{
		mlx_clean(w->mlx);
		exit(0);
	}

	if (key == 126)
    {
      if(!(worldMap[(int)(w->posX + w->dirX * moveSpeed)][(int)w->posY]))
      	w->posX += w->dirX * moveSpeed;
      if(!(worldMap[(int)w->posX][(int)(w->posY + w->dirY * moveSpeed)]))
      	w->posY += w->dirY * moveSpeed;
    }
    //move backwards if no wall behind you
    if (key == 125)
    {
      if(!(worldMap[(int)(w->posX - w->dirX * moveSpeed)][(int)w->posY]))
      	w->posX -= w->dirX * moveSpeed;
      if(!(worldMap[(int)w->posX][(int)(w->posY - w->dirY * moveSpeed)]))
      	w->posY -= w->dirY * moveSpeed;
    }
    //rotate to the right
    if (key == 124)
    {
    	//both camera direction and camera plane must be rotated
    	double oldDirX = w->dirX;
    	w->dirX = w->dirX * cos(-rotSpeed) - w->dirY * sin(-rotSpeed);
    	w->dirY = oldDirX * sin(-rotSpeed) + w->dirY * cos(-rotSpeed);
    	double oldPlaneX = w->planeX;
    	w->planeX = w->planeX * cos(-rotSpeed) - w->planeY * sin(-rotSpeed);
    	w->planeY = oldPlaneX * sin(-rotSpeed) + w->planeY * cos(-rotSpeed);
    }
    //rotate to the left
    if (key == 123)
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = w->dirX;
      w->dirX = w->dirX * cos(rotSpeed) - w->dirY * sin(rotSpeed);
      w->dirY = oldDirX * sin(rotSpeed) + w->dirY * cos(rotSpeed);
      double oldPlaneX = w->planeX;
      w->planeX = w->planeX * cos(rotSpeed) - w->planeY * sin(rotSpeed);
      w->planeY = oldPlaneX * sin(rotSpeed) + w->planeY * cos(rotSpeed);
    }
    mlx_destroy_image(w->mlx->mlx_p, w->mlx->img);
    w->mlx->img = mlx_new_image(w->mlx->mlx_p, 600, 600);
    w->mlx->data = mlx_get_data_addr(w->mlx->img, &w->mlx->bpp, &w->mlx->sl, &w->mlx->endian);
    draw(w);
	mlx_put_image_to_window(w->mlx->mlx_p, w->mlx->win_p, w->mlx->img, 0, 0);
	return (0);
}

void			my_pixel_put_to_image(char *data, int x, int y, int color, t_mlx *mlx)
{
	data[y * mlx->sl + x * mlx->bpp / 8] = color;
	data[y * mlx->sl + x * mlx->bpp / 8 + 1] = color >> 8;
	data[y * mlx->sl + x * mlx->bpp / 8 + 2] = color >> 16;
}

void	draw(t_wolf *w)
{
	for(int x = 0; x < 600; x++)
	{
		//calculate ray position and direction
		w->cameraX = 2.0 * x / ((double)600.0) - 1; //x-coordinate in camera space
		w->rayDirX = w->dirX + w->planeX * w->cameraX;
		w->rayDirY = w->dirY + w->planeY * w->cameraX;
		//which box of the map we're in
		w->mapX = (int)w->posX;
		w->mapY = (int)w->posY;

		//length of ray from current position to next x or y-side
		/*w->sideDistX;
		w->sideDistY;*/

		 //length of ray from one x or y-side to next x or y-side
		w->deltaDistX = fabs(1.0 / w->rayDirX);
		w->deltaDistY = fabs(1.0 / w->rayDirY);
		/*w->perpWallDist;*/

		//what direction to step in x or y-direction (either +1 or -1)
		/*int stepX;
		int stepY;*/

		w->hit = 0; //was there a wall hit?
		/*int side; */ //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if (w->rayDirX < 0)
		{
			w->stepX = -1;
			w->sideDistX = (w->posX - w->mapX) * w->deltaDistX;
		}
		else
		{
			w->stepX = 1;
			w->sideDistX = (w->mapX + 1.0 - w->posX) * w->deltaDistX;
		}
		if (w->rayDirY < 0)
		{
			w->stepY = -1;
			w->sideDistY = (w->posY - w->mapY) * w->deltaDistY;
		}
		else
		{
			w->stepY = 1;
			w->sideDistY = (w->mapY + 1.0 - w->posY) * w->deltaDistY;
		}
		//perform DDA
		while (w->hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (w->sideDistX < w->sideDistY)
			{
				w->sideDistX += w->deltaDistX;
				w->mapX += w->stepX;
				w->side = 0;
			}
			else
			{
			w->sideDistY += w->deltaDistY;
			w->mapY += w->stepY;
			w->side = 1;
			}
			//Check if ray has hit a wall
			if (worldMap[w->mapX][w->mapY] > 0)
			w->hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if (w->side == 0)
			w->perpWallDist = (w->mapX - w->posX + (1 - w->stepX) / 2) / w->rayDirX;
		else
			w->perpWallDist = (w->mapY - w->posY + (1 - w->stepY) / 2) / w->rayDirY;

		//Calculate height of line to draw on screen
		w->lineHeight = (int)(600 / w->perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		w->drawStart = -w->lineHeight / 2 + 600 / 2;
		if (w->drawStart < 0)
			w->drawStart = 0;
		w->drawEnd = w->lineHeight / 2 + 600 / 2;
		if (w->drawEnd >= 600)
			w->drawEnd = 600 - 1;

		//choose wall color
		if (worldMap[w->mapX][w->mapY] == 1)
			w->mlx->color = 0xff0000;
		else if (worldMap[w->mapX][w->mapY] == 2)
			w->mlx->color = 0x178c05;
		else if (worldMap[w->mapX][w->mapY] == 3)
			w->mlx->color = 0x0055ff;
		else if (worldMap[w->mapX][w->mapY] == 4)
			w->mlx->color = 0xffffff;
		else
			w->mlx->color = 0xffff00;

		//give x and y sides different brightness
		if (w->side == 1)
			w->mlx->color /= 2;

		//draw the pixels of the stripe as a vertical line
		while (w->drawStart <= w->drawEnd)
		{	
			my_pixel_put_to_image(w->mlx->data, x, w->drawStart, w->mlx->color, w->mlx);
			w->drawStart++;
	 	}
	}
}

int main(void)
{
	t_mlx  *mlx;
	t_wolf *w;

	w = (t_wolf *)malloc(sizeof(t_wolf));
	w->mlx = (t_mlx *)malloc(sizeof(t_mlx));
	w->mlx->mlx_p = mlx_init();
	w->posX = 22;
	w->posY = 12;  //x and y start position
	w->dirX = -1;
	w->dirY = 0; //initial direction vector
	w->planeX = 0;
	w->planeY = 0.66; //the 2d raycaster version of camera plane

	w->time = 0; //time of current frame
	w->oldTime = 0; //time of previous frame
	w->mlx->img = mlx_new_image(w->mlx->mlx_p, 600, 600);
	w->mlx->data = mlx_get_data_addr(w->mlx->img, &w->mlx->bpp, &w->mlx->sl, &w->mlx->endian);
	w->mlx->win_p = mlx_new_window(w->mlx->mlx_p, 600, 600, "Ololo");
	draw(w);
	mlx_put_image_to_window(w->mlx->mlx_p, w->mlx->win_p, w->mlx->img, 0, 0);
	mlx_hook(w->mlx->win_p, 2, 5, hooks, w);
	mlx_loop(w->mlx->mlx_p);
	return (0);
	}
