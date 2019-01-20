#include "RTv1.h"

/* 
how to find if ray git the sphere? if C is sphere center, where C =(cx, cy, cz),
then if dot((A + t*B - C), (A + t*B - C)) = R * R then the ray hits the sphere
dot((A+t*B-C),(A+t*B-C))=R*R => t*t*dot(B,B) + 2*t*dot(B,A-C) + dot(A-C,A-C) - R*R=0

dot (a, b) - скалярний добуток: a * b = |a| * |b| * cos(a, b)
*/

void error(t_sdl *s, char *str)
{
	ft_putendl(str);
	if (s->win != NULL)
		SDL_DestroyWindow(s->win);
	free(s);
	SDL_Quit();
	exit(1);
}

void		init(t_sdl	*sdl)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	if (!(sdl->win = SDL_CreateWindow("AYOUUU, BITCHEZZZ", 100, 100, WDTH, HGHT, 0)) ||
		!(sdl->surf = SDL_GetWindowSurface(sdl->win)))
		error(sdl, "Error while initializing sdl!\n");
	ft_memset(sdl->surf->pixels, 0, WDTH * HGHT * sizeof(int));
	sdl->ray = (t_ray *)malloc(sizeof(t_ray));

}

t_vector	v_multi(float a, t_vector b)
{
	t_vector tmp = (t_vector){a, a, a};
	return (tmp * b); 
}

float		v_length(t_vector a)
{
	return (sqrt((float)(a[0] * a[0] + a[1] * a[1] + a[2] * a[2])));
}

t_vector	unit_vector(t_vector b) // Відбувається нормалізація вектора, тобто приведення до ветокра колінеарного початковому, але з довжиною 1
{
	return (v_div(b, v_length(b)));
}

t_vector	v_div(t_vector a, float b)
{
	t_vector	tmp;

	tmp = (t_vector){b, b, b};

	return (a / tmp);
}

t_vector	v_add(t_vector a, float b)
{
	t_vector	tmp;

	tmp = (t_vector){b, b, b};
	return (a + tmp);
}

t_vector	point_vector(float f, t_ray *ray)
{
	t_vector i;

	i = v_multi(f, ray->b);
	return (ray->a + i);
}

t_vector	color(t_ray *ray)
{
	float		t;
	t_vector	first;
	t_vector	second;
	t_vector	center;
	t_vector	unit_direction;

	first = (t_vector){1.0, 1.0, 1.0};
	second = (t_vector){0.5, 0.7, 1.0};
	center = (t_vector){0.0, 0.0, -1.0};
	t = hit_sphere(center, 0.5, ray);
	if (t > 0.0)
	{
		t_vector n = unit_vector(point_vector(t, ray) - center);
		n = v_add(n, 1.0);
		return(v_multi(0.5, n));
	}
	unit_direction = unit_vector(ray->b);
	t = 0.5 * ((float)unit_direction[1] + 1.0);
	return ((v_multi((1.0 - t), first) + v_multi(t, second)));
}

float		dot(t_vector a, t_vector b)
{
	return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
}	

float			hit_sphere(t_vector center, float radius, t_ray *ray)
{
	t_vector oc;
	float	a;
	float	b;
	float	c;
	float	disc;

	oc = ray->a - center;
	a = dot(ray->b, ray->b);
	b = 2.0 * dot(oc, ray->b);
	c = dot(oc, oc) - radius * radius;
	disc = b * b - 4 * a * c; 
	if (disc < 0)
		return (-1.0);
	else
		return((-b - sqrt(disc)) / (2.0 * a));
}

int			main(void)
{
	t_sdl	*sdl;

	int	flag = 0;
	int nx = WDTH;
	int ny = HGHT;
	int j = 0;
	int i = 0;
	int sdl_color = 0;
	int r;
	int g;
	int b;
	float u;
	float v;
	int ir;
	int ib;
	int ig;
	t_vector	low_l_corner = (t_vector){-2.0, 1.0, -1.0}; // Змінив лівий кут, оскільки ітерації йдуть зілва направо, згори вниз
	t_vector	horizontal = (t_vector){4.0, 0.0, 0.0};
	t_vector	vertical = (t_vector){0.0, -2.0, 0.0}; // Змінив ^
	t_vector	origin = (t_vector){0.0, 0.0, 0.0};
	t_vector	col;
	
	if (!(sdl = (t_sdl *)malloc(sizeof(t_sdl))))
		error(sdl, "Error while initializing!\n");
	init(sdl);
	while (j < ny)
	{
		i = 0;
		while (i < nx)
		{
			u = (float)(i) / (float)(nx);
			v = (float)(j) / (float)(ny);
			sdl->ray->a = origin;
			sdl->ray->b = low_l_corner + v_multi(u, horizontal) + v_multi(v, vertical);
			col = color(sdl->ray);
			r = (int)(255.99 * col[0]);
			g = (int)(255.99 * col[1]);
			b = (int)(255.99 * col[2]);
			sdl_color = SDL_MapRGB(sdl->surf->format, r, g, b);
			((int *)sdl->surf->pixels)[j * WDTH + i] = sdl_color;
			i++;
		}
		j++;
	}
	while (!flag)
	{
		SDL_WaitEvent(&sdl->event);
		SDL_UpdateWindowSurface(sdl->win);
		if (sdl->event.type == SDL_QUIT || sdl->event.key.keysym.sym == SDLK_ESCAPE)
		{
			flag = 1;
			break;
		}
	}
	SDL_DestroyWindow(sdl->win);
	SDL_Quit();
	return (0);
}