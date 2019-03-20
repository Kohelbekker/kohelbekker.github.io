/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 16:13:18 by aperesad          #+#    #+#             */
/*   Updated: 2019/03/08 16:13:20 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# define WDTH 600
# define HGHT 600
# define MAX_I 2147483646
# define MAX(X, Y) (((X)< (Y)) ? (Y) : (X))
# define MIN(X, Y) (((X)< (Y)) ? (X) : (Y))
# define DEG (M_PI / 180)

# include "SDL.h"
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include "../libft/libft.h"

typedef double t_vector	__attribute__	((vector_size (3 * sizeof(double))));

typedef struct			s_shape
{
	int					type;
	t_vector			axis_v;
	t_vector			center;
	double				radius;
	t_vector			color;
	int					specular;
	double				angle;
	double				clos_t;
	struct s_shape		*next;
}						t_shape;

typedef struct			s_tmp
{
	int					type;
	t_vector			axis_v;
	t_vector			center;
	double				radius;
	t_vector			color;
	int					specular;
	double				angle;
	double				clos_t;
}						t_tmp;

typedef struct			s_calc
{
	t_vector			vec_l;
	t_vector			vec_r;
	double				n_dot_l;
	double				r_dot_v;
	t_vector			point;
	t_vector			normal;
	t_vector			view;
}						t_calc;

typedef struct			s_light
{
	int					type;
	double				intensity;
	t_vector			position;
	struct s_light		*next;
}						t_light;

typedef	struct			s_ray
{
	t_vector			a;
	t_vector			b;
}						t_ray;

typedef struct			s_sdl
{
	double				min;
	double				max;
	int					hit;
	t_calc				*calc;
	t_vector			cam_rot;
	double				x_unit;
	double				y_unit;
	double				viewport_size;
	double				projection_plane_z;
	t_vector			background;
	SDL_Event			event;
	SDL_Window			*win;
	SDL_Surface			*surf;
	t_ray				*ray;
	t_tmp				*closest_shape;
	t_tmp				*closest_light;
	t_shape				*shapes;
	t_light				*lights;
}						t_sdl;


void					param1(t_sdl *sdl, t_shape *tmp, char **word, int i);
void					param2(t_sdl *sdl, t_shape *tmp, char **word, int i);
void					param3(t_sdl *sdl, t_shape *tmp, char **word, int i);
void					param4(t_sdl *sdl, t_shape *tmp, char **word, int i);
double					hit_loop(t_sdl *sdl, t_ray *ray, double t);
double					plane_t(t_sdl *sdl, t_ray *ray, double t);
t_tmp					*clos_intersac(t_sdl *sdl, t_ray *ray,
						double min_t, double max_t);
double					compute_lighting(t_sdl *sdl, int s, double intensity);
double					light_loop(t_sdl *sdl, int s, double intensity);
t_vector				check_colors(t_vector col);
int						draw(t_sdl *sdl, double u, double v, int sdl_color);
t_sdl					*sdl_clean(t_sdl *sdl);
void					zero_error(char *str);
void					error(t_sdl *sdl, char *str);
void					free_str(char **str);
double					*hit_sphere(t_ray *ray, t_shape *shape, double a,
						double b);
double					hit_plane(t_ray *ray, t_shape *shape);
double					*hit_cylinder(t_ray *ray, t_shape *shape, double a,
						double b);
double					*hit_cone(t_ray *ray, t_shape *shape, double a,
						double b);
t_shape					*add_list(t_sdl *sdl, t_shape *new);
t_light					*add_light(t_sdl *sdl, t_light *new);
void					init(t_sdl	*sdl, int fd);
int						av_check(char *av);
int						main(int ac, char **av);
void					get_scene(t_sdl *sdl, int fd);
void					check_first_line(t_sdl *sdl, char *str);
void					get_shape(t_sdl *sdl, char *str);
void					set_cam(t_sdl *sdl, int i, char **line);
t_vector				rot(t_vector a, t_sdl *sdl);
double					x_part(t_sdl *sdl, double x, double y, double z);
double					y_part(t_sdl *sdl, double x, double y, double z);
double					z_part(t_sdl *sdl, double x, double y, double z);
void					light_intens(t_sdl *sdl, t_light *tmp, char **word);
void					light_type(t_sdl *sdl, t_light *tmp, char **word);
void					light_center(t_sdl *sdl, t_light *tmp, char **word);
void					set_sphere(t_sdl *sdl, char **line, int i);
void					set_plane(t_sdl *sdl, char **line, int i);
void					set_cylinder(t_sdl *sdl, char **line, int i);
void					set_cone(t_sdl *sdl, char **line, int i);
void					set_light(t_sdl *sdl, char **line, int i);
void					shape_angle(t_sdl *sdl, t_shape *tmp, char **word);
void					shape_color(t_sdl *sdl, t_shape *tmp, char **word);
void					shape_specular(t_sdl *sdl, t_shape *tmp, char **word);
void					shape_center(t_sdl *sdl, t_shape *tmp, char **word);
void					shape_axis(t_sdl *sdl, t_shape *tmp, char **word);
void					shape_radius(t_sdl *sdl, t_shape *tmp, char **word);
int						*check_cycle(t_sdl *sdl, int j, int a, char **word);
int						last_char(char *str);
int						row_nbr(char **str);
t_vector				int_to_vec(int *a, double div);
t_vector				v_div(double b, t_vector a);
void					shape2_calc(t_sdl *sdl, t_ray *ray,
						t_tmp *closest_shape);
void					shape4_calc(t_sdl *sdl, t_ray *ray,
						t_tmp *closest_shape);
void					shape3_calc(t_sdl *sdl, t_ray *ray,
						t_tmp *closest_shape);
t_vector				trace_ray(t_sdl *sdl, t_ray *ray, double min_t,
						double max_t);
t_vector				v_multi(double a, t_vector b);
double					v_length(t_vector a);
t_vector				unit_vector(t_vector b);
t_vector				point_vector(double f, t_ray *ray);
double					dot(t_vector a, t_vector b);

#endif
