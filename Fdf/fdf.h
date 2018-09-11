/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 17:51:58 by aperesad          #+#    #+#             */
/*   Updated: 2018/07/02 17:52:01 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define W_HGHT 1600
# define W_WID  2000
# define DIST	30
# define DIST_Z 15
# define ABS(x)  (((x) < 0) ? -(x) : (x))
# define SPACE(x) (x == ' ' || x == '\t' || x == '\n')

# include <mlx.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <math.h>

typedef	struct	s_points
{
	double		x;
	double		y;
	double		z;
	double		h;
	int			color;
}				t_points;

typedef struct	s_map
{
	int			width;
	int			height;
	int			z_min;
	int			z_max;
	double		scale;
	double		cam_x;
	double		cam_y;
	t_points	**points;
}				t_map;

typedef struct	s_mlx
{
	void		*mlx_p;
	void		*win_p;
	t_map		*map;
}				t_mlx;

typedef struct	s_brez
{
	int			dy;
	int			dx;
	int			sig_x;
	int			sig_y;
	int			err;
	int			err2;
}				t_brez;

int				error(char *str);
t_points		angle_mat(t_points a, t_mlx *mlx);
int				first_line_width(char *tmp);
t_map			*find_z(t_map *m, int x, int y);
void			make_points(char *tmp, int l, t_map *map);
int				lines_n_chars(char *av, t_map **map, int chrs, int lines,
				int f_line);
t_map			*validate(char **av, int fd, int j);
t_mlx			*mlx_make(char *av, t_map *map);
int				hooks(int key, t_mlx *mlx);
t_mlx			*clean_mlx(t_mlx *mlx);
t_points		center(t_points a, t_mlx *mlx);
t_points		scale_mat(t_points p, t_mlx *mlx);
int				lines_nb(char *av, t_map **map, int lines);
void			points(t_points a1, t_points a2, t_mlx *mlx);
void			ft_draw(t_mlx *mlx);
void			hook_translate(int key, t_mlx *mlx);
void			make_traslation(int a, t_mlx *mlx, char c);
void			hook_scale(int key, t_mlx *mlx);
void			make_scale(t_mlx *mlx, int key);
void			hook_rotate(int key, t_mlx *mlx);
void			make_rotate_ox(t_mlx *mlx, double ang, double b);
void			make_rotate_oy(t_mlx *mlx, double ang,
				double a);
void			make_rotate_oz(t_mlx *mlx, double ang,
				double a, double b);
void			make_pointsonly(t_mlx *mlx);
int				hook_pointsonly(int key, t_mlx *mlx);
void			zero_position(int key, t_mlx *mlx);
t_map			*scale(t_map *m);

#endif
