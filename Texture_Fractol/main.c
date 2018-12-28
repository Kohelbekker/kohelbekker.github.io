/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 16:15:51 by aperesad          #+#    #+#             */
/*   Updated: 2018/10/02 16:15:54 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		fractals(t_fract *f, t_draw *d)
{
	if (ft_strcmp(f->man->name, "mandelbrot") == 0)
		mandelbrot(f, d);
	else if (ft_strcmp(f->man->name, "burn") == 0)
		burn(f, d);
	else if (ft_strcmp(f->man->name, "buffalo") == 0)
		buffalo(f, d);
	else if (ft_strcmp(f->man->name, "heart") == 0)
		heart(f, d);
	else if (ft_strcmp(f->man->name, "tricorn") == 0)
		tricorn(f, d);
	else
		julia(f, d);
}

void		find_fract(t_fract *f, char *av)
{
	if (ft_strcmp(av, "mandelbrot") == 0)
		f->man = init_mandel(av);
	else if (ft_strcmp(av, "julia") == 0)
		f->man = init_julia(av);
	else if (ft_strcmp(av, "burn") == 0)
		f->man = init_burn(av);
	else if (ft_strcmp(av, "buffalo") == 0)
		f->man = init_buffalo(av);
	else if (ft_strcmp(av, "heart") == 0)
		f->man = init_heart(av);
	else if (ft_strcmp(av, "tricorn") == 0)
		f->man = init_mandel(av);
	else
		error("No such fractol! List of available fractlas:\n\t\tmandelbrot"
			"\n\t\tjulia\n\t\tburn\n\t\tbuffalo\n\t\theart\n\t\ttricorn");
}

void		init(t_fract *f, char *av)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	if (!(f->mlx->win_p = SDL_CreateWindow(av, 100, 100, WDTH, HGHT, 0)) ||
		!(f->mlx->img = SDL_CreateRenderer(f->mlx->win_p, -1, 0)) ||
		!(f->mlx->pixels = (Uint32 *)malloc(WDTH * HGHT * sizeof(Uint32))) ||
		!(f->mlx->texture = SDL_CreateTexture(f->mlx->img, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, WDTH, HGHT)))
		mlx_clean(f->mlx);
	f->k_ind1 = 0.08;
	f->k_ind2 = 0.04;
	f->k_ind3 = 0.012;
	f->c_ind = 1;
	f->byte_ind = 255;
	f->byte_c = 50;
	f->flag = 0;
}

int			main(int ac, char **av)
{
	t_fract	*f;

	if (ac != 2)
		error("usage: ./fractol [ mandelbrot / julia / burn /"
			"buffalo / heart / tricorn ]\n");
	if (!(f = (t_fract *)malloc(sizeof(t_fract))) ||
		!(f->mlx = (t_mlx *)malloc(sizeof(t_mlx))))
		error1(f, "Error while initializing mlx variables!\n");
	find_fract(f, av[1]);
	init(f, av[1]);
	draw(f);
	f->exit = 0;
	printf("Ololololololo\n");
	while (!(f->exit))
	{
		SDL_WaitEvent(&f->mlx->mlx_p);
		SDL_UpdateTexture(f->mlx->texture, NULL, f->mlx->pixels, WDTH * sizeof(Uint32));
		if (f->mlx->mlx_p.type == SDL_KEYDOWN)
			hooks(f);
		if (f->mlx->mlx_p.type == SDL_MOUSEBUTTONDOWN)
			zoom_hook(f);
		mouse_julia(f);
		SDL_RenderClear(f->mlx->img);
		SDL_RenderCopy(f->mlx->img, f->mlx->texture, NULL, NULL);
		SDL_RenderPresent(f->mlx->img);
	}
	return (0);
}
