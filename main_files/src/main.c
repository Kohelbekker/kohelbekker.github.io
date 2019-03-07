/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 18:23:04 by aperesad          #+#    #+#             */
/*   Updated: 2019/03/07 18:23:06 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void		init(t_sdl	*sdl, char *av, int fd)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	if (!(sdl->win = SDL_CreateWindow("WORK, BLYYYAT'", 100, 100, WDTH, HGHT, 0)) ||
		!(sdl->surf = SDL_GetWindowSurface(sdl->win)))
		error(sdl, "Error while initializing sdl!\n");
	ft_memset(sdl->surf->pixels, 0, WDTH * HGHT * sizeof(int));
	sdl->ray = (t_ray *)malloc(sizeof(t_ray));
	sdl->viewport_size = 1.0;
	sdl->projection_plane_z = 1;
	sdl->background = (t_vector){0, 0, 0};
	sdl->x_unit = sdl->viewport_size / (double)WDTH;
	sdl->y_unit = sdl->viewport_size / (double)HGHT;
	sdl->exit = 0;
	get_scene(sdl, av, fd);

}

int			av_check(char *av)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 3;
	str = (char *)malloc(sizeof(char) * 5);
	str[4] = '\0';
	while (av[i])
		i++;
	i--;
	while (j > -1)
	{
		str[j] = av[i];
		j--;
		i--;
	}
	if (strcmp(str, ".rtv") == 0)
	{
		free(str);
		return (1);
	}
	free(str);
	return (0);
}

int			main(int ac, char **av)
{
	t_sdl	sdl;
	int		fd;
	char	*str;

	if (ac != 2 || (av_check(av[1])) == 0)
		zero_error("No input file / more than 1 input file / wrong format\n");
	if (!(fd = open(av[1], O_RDONLY)) || (read(fd ,&str, 0)) == -1)
		zero_error("File is empty or incorrect\n");
	free(str);
	init(&sdl, av[1], fd);
	close(fd);
	draw(&sdl);
	while (1)
	{
		SDL_WaitEvent(&sdl.event);
		SDL_UpdateWindowSurface(sdl.win);
		if (sdl.event.type == SDL_QUIT || (sdl.event.type == SDL_KEYDOWN && sdl.event.key.keysym.sym == SDLK_ESCAPE))
		{
			sdl_clean(&sdl);
			break;
		}
	}
	return (0);
}
