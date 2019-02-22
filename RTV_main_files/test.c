#include "libft/libft.h"
#include "new_RTv1.h"
#include <stdio.h>

SDL_Surface		*load_texture(char *path, SDL_Surface *wolf)
{
	SDL_Surface		*stock;
	SDL_Surface		*surface;

	stock = SDL_LoadBMP(path);
	if (stock == NULL)
	{
		printf("Error while loading a %s texture file\n", path);
		exit(1);
	}
	surface = SDL_ConvertSurfaceFormat(stock, wolf->format->format, 0);
	SDL_FreeSurface(stock);
	return (surface);
}

int		main()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window	*win;
	SDL_Surface	*surf;
	SDL_Surface *bpm;

	win = SDL_CreateWindow("test", 100, 100, 400, 400, 0);
	surf =  SDL_GetWindowSurface(win);
	ft_memset(surf->pixels, 0, WDTH * HGHT * sizeof(int));
	bpm = load_texture("1.bmp");
	int i = 0;
	int j = 0;
	while (i < 400)
	{
		j = 0;
		while (j < 400)
		{
			if (i > 100 && i < 150)
				((int *)surf->pixels)[j * 400 + i] = 0xffa500;
			j++;
		}
		i++
	}

	while (!(f->exit))
	{
		SDL_WaitEvent(&f->mlx->mlx_p);
		SDL_UpdateWindowSurface(f->mlx->win_p);
	}
}
