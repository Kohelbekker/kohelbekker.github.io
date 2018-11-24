/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:22:55 by aperesad          #+#    #+#             */
/*   Updated: 2018/10/24 20:11:39 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# define HGHT 1000
# define WDTH 1000
# define SPC(x) (x != ' ' && x != '\t' && x != '\v' && x != '\f' && x != '\n')
# define MOVE ((M_PI / 180) * 7)
# define ROT ((M_PI / 180) * 5)
# define ROT2 ((M_PI / 180) * 9)
# define MOVE2 ((M_PI / 180) * 14)
# define TEX_W 64
# define TEX_H 64

# include <math.h>
# include <mlx.h>
# include <stdlib.h>
# include "libft/libft.h"
# include <fcntl.h>

typedef struct	s_mlx
{
	void		*mlx_p;
	void		*win_p;
	void		*img;
	char		*data;
	int			bpp;
	int			sl;
	int			ed;
	int			color;
}				t_mlx;

typedef struct	s_map
{
	int			**map;
	int			w;
	int			h;
}				t_map;

typedef struct	s_hook
{
	int			forw;
	int			back;
	int			left;
	int			right;
	int			shift;
}				t_hook;

typedef struct	s_wolf
{
	t_mlx		tex[12];
	t_mlx		*mlx;
	t_map		*map;
	t_hook		*hook;
	int			i;
	double		camx;
	double		x_ray;
	double		y_ray;
	int			x;
	int			y;
	double		l_ox;
	double		l_oy;
	double		delt_x;
	double		delt_y;
	double		ray_l;
	int			step_x;
	int			step_y;
	int			wall;
	int			side;
	int			line_h;
	int			wall_start;
	int			wall_end;
	double		x_wall;
	int			x_t;
	int			y_t;
	int			n_t;
	double		start_x;
	double		start_y;
	double		vect_x;
	double		vect_y;
	double		ang_x;
	double		ang_y;
	int			tmp;
	int			flag;
	double		speed;
	double		rotate;
	double		floor_wall_x;
	double		floor_wall_y;
	double		pers_dist;
	double		tmp_dist;
	double		corr;
	double		tmp_floor_x;
	double		tmp_floor_y;
	int			tex_floor_x;
	int			tex_floor_y;
	double		tmp_startx;
	double		tmp_starty;
	double		oldvect_x;
	double		oldang_x;
}				t_wolf;

int				error(char *str);
int				error1(char *str, t_wolf *w);
int				exit_x(void);
t_mlx			*mlx_clean(t_mlx *mlx);
void			my_pixel_put_to_image2(char *data, int x, int y, t_wolf *w);
void			my_pixel_put_to_image3(char *data, int x, int y, t_wolf *w);
void			wall_position(t_wolf *w);
void			draw_floor_and_ceiling(t_wolf *w);
int				movehook(t_wolf *w);
int				hooks_released(int key, t_wolf *w);
int				hooks_pressed(int key, t_wolf *w);
void			draw(t_wolf *w);
void			init(t_wolf *w);
int				main(int ac, char **av);
void			basic_check(char *av, t_wolf *w, int i);
void			make_map(char *av, t_wolf *w, int i, int j);
void			start_position(t_wolf *w, int a, int i);
int				check_map(char *av, t_wolf *w);
void			move_forward(t_wolf *w);
void			move_back(t_wolf *w);
void			turn_left(t_wolf *w);
void			turn_right(t_wolf *w);
void			my_pixel_put_to_image(char *data, int x, int y, t_wolf *w);
void			ray_step(t_wolf *w);
void			ray_length(t_wolf *w);
void			texture_xy(t_wolf *w);
void			pre_draw(t_wolf *w);
void			create_texture(t_wolf *w);
void			texture_type(t_wolf *w);
void			reload(t_wolf *w);
void			init2(t_wolf *w);

#endif
