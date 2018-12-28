/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 12:53:58 by aperesad          #+#    #+#             */
/*   Updated: 2018/09/17 13:11:33 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define HGHT 800
# define WDTH 800

# include "/Users/aperesad/.brew/Cellar/sdl2/2.0.9/include/SDL2/SDL.h"
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include "libft/libft.h"
# include <stdio.h>

typedef struct		s_draw
{
	double			c_im;
	double			c_re;
	double			z_re;
	double			z_im;
	double			z_sim;
	double			z_sre;
	int				n;
	int				y;
	int				x;
}					t_draw;

typedef struct		s_mandel
{
	char			*name;
	double			min_im;
	double			max_im;
	double			min_re;
	double			max_re;
	double			cur_re;
	double			cur_im;
	double			jul_cr;
	double			jul_ci;
	int				max_iter;
	int				start;
}					t_mandel;

typedef struct		s_mlx
{
	SDL_Event		mlx_p;
	SDL_Window		*win_p;
	SDL_Surface		*img;
	char			*data;
	int				bpp;
	int				sl;
	int				endian;
	int				color;
}					t_mlx;

typedef struct		s_fract
{
	t_mlx			*mlx;
	t_mandel		*man;
	double			zoom;
	double			k;
	double			k_ind1;
	double			k_ind2;
	double			k_ind3;
	double			c_ind;
	int				byte_ind;
	int				byte_c;
	int				flag;
	int				start;
	int				end;
	double			re;
	double			im;
	int				ind;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	int				exit;
}					t_fract;

int					main(int ac, char **av);
void				init(t_fract *f, char *av);
void				find_fract(t_fract *f, char *av);
t_mlx				*mlx_clean(t_mlx *mlx);
int					error(char *str);
int					error1(t_fract *f, char *str);
int					exit_x(void);
void				fractals(t_fract *f, t_draw *d);
void				my_pixel_put_to_image(t_fract *f, t_draw *d);
void				my_pixel_put_to_image2(t_fract *f, t_draw *d);
int					mouse_julia(t_fract *f);
void				scale(t_fract *f);
int					zoom_hook(t_fract *f);
void				rotation(int key, t_fract *f);
void				iterations(int key, t_fract *f);
void				switch_color(int key, t_fract *f);
void				get_back(t_fract *f);
int					hooks(t_fract *f);
t_mandel			*init_burn(char *av);
t_mandel			*init_mandel(char *av);
t_mandel			*init_heart(char *av);
t_mandel			*init_buffalo(char *av);
t_mandel			*init_julia(char *av);
void				mandelbrot(t_fract *f, t_draw *d);
void				heart(t_fract *f, t_draw *d);
void				tricorn(t_fract *f, t_draw *d);
void				buffalo(t_fract	*f, t_draw *d);
void				burn(t_fract *f, t_draw *d);
void				julia(t_fract *f, t_draw *d);
void				*draw(t_fract *p_f);

#endif
