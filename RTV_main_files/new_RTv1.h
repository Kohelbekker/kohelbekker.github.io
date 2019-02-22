# ifndef NEW_RTV1_H
# define NEW_RTV1_H

# define WDTH	600
# define HGHT	600
# define MAX_I	2147483646
# define MAX(X, Y)	(((X)< (Y)) ? (Y) : (X))
# define MIN(X, Y)	(((X)< (Y)) ? (X) : (Y))
# define DEG	(M_PI / 180)

#include <stdio.h>
#include "SDL.h"
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include "libft/libft.h"

typedef double t_vector __attribute__ ((vector_size (3 * sizeof(double))));

typedef struct 			s_shape
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

typedef struct			s_light
{
	int					type;
	double				intensity;
	t_vector			position;
	struct s_light		*next;
}						t_light;

typedef	struct 			s_ray
{
	t_vector			a;
	t_vector			b;
	double				r;
}						t_ray;

typedef struct 			s_sdl
{
	t_vector			cam_rot;
	double				x_unit;
	double				y_unit;
	int					exit;
	double				viewport_size;
	double				projection_plane_z;
	t_vector			background;
	SDL_Event			event;
	SDL_Window			*win;
	SDL_Surface			*surf;
	t_ray				*ray;	
	t_shape				*shapes;
	t_light				*lights;
	//t_shape			shapes[7];
	//t_light			lights[3];
}				t_sdl;

t_vector		v_multi(double a, t_vector b);
double			v_length(t_vector a);
t_vector		unit_vector(t_vector b);
t_vector		point_vector(double f, t_ray *ray);
void 			error(t_sdl *sdl, char *str);
double			dot(t_vector a, t_vector b);
t_vector		Check_colors(t_vector col);
void			init(t_sdl	*sdl, char *av, int fd);
double			*hit_sphere(t_ray *ray, t_shape *sphere);
t_shape			ClosestIntersaction(t_sdl *sdl, t_ray *ray, double min_t, double max_t);
double			ComputeLighting(t_sdl *sdl, t_vector point, t_vector normal, t_vector view, int s);
t_vector		TraceRay(t_sdl *sdl, t_ray *ray, double min_t, double max_t);
int				main(int ac, char **av);
t_vector		v_div(double b, t_vector a);
int				rotation(float ang, int flag, t_sdl *sdl);
int				hooks(t_sdl *sdl);
int				draw(t_sdl *sdl);
t_sdl			*sdl_clean(t_sdl *sdl);
t_vector		rot(t_vector a, t_sdl *sdl);
double			x_part(t_sdl *sdl, double x, double y, double z);
double			y_part(t_sdl *sdl, double x, double y, double z);
double			z_part(t_sdl *sdl, double x, double y, double z);
void			zero_error(char *str);
int				av_check(char *av);


////////////////////////////////////////////////////////////////////////
void			get_scene(t_sdl *sdl, char *av, int fd);
t_light			*ft_lstadd_light(t_sdl *sdl, t_light *new);
t_shape			*ft_lstadd_shape(t_sdl *sdl, t_shape *new);
void			check_first_line(t_sdl *sdl, char *str);
void			set_camera(t_sdl *sdl, int i, char **line, int j, int a);
t_vector		int_to_vec(int *a, double div);
int				row_nbr(char **str);
int				last_char(char *str);
void			get_shape(t_sdl *sdl, char *str);
t_shape			*set_cone(t_sdl *sdl, char **line, int i);
t_shape			*set_cylinder(t_sdl *sdl, char **line, int i);
t_light			*set_light(t_sdl *sdl, char **line, int i);
t_shape			*set_plane(t_sdl *sdl, char **line, int i);
t_shape			*set_sphere(t_sdl *sdl, char **line, int i);
void			shape_specular(t_sdl *sdl, t_shape *tmp, char **word);
void			shape_color(t_sdl *sdl, t_shape *tmp, char **word);
void			shape_angle(t_sdl *sdl, t_shape *tmp, char **word);
void			shape_radius(t_sdl *sdl, t_shape *tmp, char **word);
void			shape_axis(t_sdl *sdl, t_shape *tmp, char **word);
void			shape_center(t_sdl *sdl, t_shape *tmp, char **word);
void			light_center(t_sdl *sdl, t_light *tmp, char **word);
void			light_type(t_sdl *sdl, t_light *tmp, char **word);
void			light_intens(t_sdl *sdl, t_light *tmp, char **word);
int				*check_cycle(t_sdl *sdl, int j, int a, char **word);
////////////////////////////////////////////////////////////////////////
# endif