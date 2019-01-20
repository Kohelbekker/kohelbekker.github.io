# ifndef RTV1_H
# define RTV1_H

# define WDTH 800
# define HGHT 400

#include <stdio.h>
#include "/Users/aperesad/.brew/Cellar/sdl2/2.0.9/include/SDL2/SDL.h"
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include "libft/libft.h"

typedef float t_vector __attribute__ ((vector_size (3 * sizeof(float))));

typedef struct	hit_record
{
	float		t;
	t_vector	p;
	t_vector	normal;
}				t_hit;

typedef	struct 	s_ray
{
	t_vector	a;
	t_vector	b;
	float		r;
}				t_ray;

typedef struct 	s_sdl
{
	SDL_Event		event;
	SDL_Window		*win;
	SDL_Surface		*surf;
	t_ray			*ray;
}				t_sdl;

void		error(t_sdl *s, char *str);
void		init(t_sdl	*sdl);
t_vector	v_multi(float a, t_vector b);
float		v_length(t_vector a);
t_vector	unit_vector(t_vector b);
t_vector	v_div(t_vector a, float b);
t_vector	v_add(t_vector a, float b);
t_vector	color(t_ray *ray);
float			hit_sphere(t_vector center, float radius, t_ray *ray);
int			main(void);
float		dot(t_vector a, t_vector b);
t_vector	point_vect(float t, t_ray *ray);
t_vector	point_vector(float f, t_ray *ray);

# endif