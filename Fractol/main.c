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
	if (!(f->mlx->mlx_p = mlx_init()) ||
		!(f->mlx->img = mlx_new_image(f->mlx->mlx_p, WDTH, HGHT)) ||
		!(f->mlx->data = mlx_get_data_addr(f->mlx->img, &f->mlx->bpp,
		&f->mlx->sl, &f->mlx->endian)) ||
		!(f->mlx->win_p = mlx_new_window(f->mlx->mlx_p, WDTH, HGHT, av)))
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
	my_threads(f);
	mlx_put_image_to_window(f->mlx->mlx_p, f->mlx->win_p, f->mlx->img, 0, 0);
	mlx_hook(f->mlx->win_p, 2, 5, hooks, f);
	mlx_mouse_hook(f->mlx->win_p, zoom_hook, f);
	mlx_hook(f->mlx->win_p, 6, 0, mouse_julia, f);
	mlx_hook(f->mlx->win_p, 17, 1L << 17, exit_x, 0);
	mlx_loop(f->mlx->mlx_p);
	return (0);
}
