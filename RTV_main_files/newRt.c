#include "new_RTv1.h"

/*
** Спробувати змінити алгоритм пошуку розвязків вадратичного рівняння
*/

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
	sdl->background = (t_vector){255, 255, 255};
	sdl->x_unit = sdl->viewport_size / (double)WDTH;
	sdl->y_unit = sdl->viewport_size / (double)HGHT;
	sdl->exit = 0;
	/*if (!(sdl->shapes = (t_shape *)malloc(sizeof(t_shape))))
			error(sdl, "Malloc error\n");
	sdl->shapes->next = NULL;
	if (!(sdl->lights = (t_light *)malloc(sizeof(t_light))))
			error(sdl, "Malloc error\n");
	sdl->lights->next = NULL;*/
	get_scene(sdl, av, fd);
	/////////////////////////////////////////////////////////////////
	// sdl->shapes[0].type = 1;										// Sphere
	// sdl->shapes[0].center = (t_vector){0.2, 0, -2.5};
	// sdl->shapes[0].radius = 1;
	// sdl->shapes[0].color = (t_vector){255, 0, 0};
	// sdl->shapes[0].specular = 500;

	// sdl->shapes[1].type = 1;										// Sphere
	// sdl->shapes[1].center = (t_vector){-7, 0, 5};
	// sdl->shapes[1].radius = 1;
	// sdl->shapes[1].color = (t_vector){0, 255, 0};
	// sdl->shapes[1].specular = 500;

	// sdl->shapes[2].type = 1;										// Sphere
	// sdl->shapes[2].center = (t_vector){1.1, 0, -5.5};
	// sdl->shapes[2].radius = 1;
	// sdl->shapes[2].color = (t_vector){0, 0, 255};
	// sdl->shapes[2].specular = 10;

	// sdl->shapes[3].type = 1;										// Sphere
	// sdl->shapes[3].center = (t_vector){0, -5001, 0};
	// sdl->shapes[3].radius = 5000;
	// sdl->shapes[3].color = (t_vector){255, 255, 0};
	// sdl->shapes[3].specular = 1000;

	// sdl->shapes[5].type = 2;										// Plane
	// sdl->shapes[5].center = (t_vector){0, 0, 8};
	// sdl->shapes[5].color = (t_vector){255, 128, 128};
	// sdl->shapes[5].specular = 800;
	// sdl->shapes[5].axis_v = (t_vector){0, 0, -1};
	// sdl->shapes[5].axis_v = unit_vector(sdl->shapes[5].axis_v);

	// sdl->shapes[6].type = 3;										// Cylinder
	// sdl->shapes[6].radius = 1;
	// sdl->shapes[6].center = (t_vector){-2, 51, -2};
	// sdl->shapes[6].color = (t_vector){255, 175, 20};
	// sdl->shapes[6].axis_v = (t_vector){0, 1, 0};
	// sdl->shapes[6].axis_v = unit_vector(sdl->shapes[6].axis_v);
	// sdl->shapes[6].specular = 1000;

	// sdl->shapes[4].type = 4;										// Cone
	// sdl->shapes[4].center = (t_vector){-3, 4, 4};
	// sdl->shapes[4].axis_v = (t_vector){0, 1, 0};
	// sdl->shapes[4].axis_v = unit_vector(sdl->shapes[4].axis_v);
	// sdl->shapes[4].angle = 30;
	// sdl->shapes[4].angle = sdl->shapes[4].angle / 2;                    ////////////////////////
	// sdl->shapes[4].specular = 1000;
	// sdl->shapes[4].color = (t_vector){55, 205, 200};
	// /////////////////////////////////////////////////////////////////

	// /////////////////////////////////////////////////////////////////
	// sdl->lights[0].type = 0; //AMBIENT
	// sdl->lights[0].intensity = 0.05;

	// sdl->lights[1].type = 1; //POINT
	// sdl->lights[1].intensity = 0.5;
	// sdl->lights[1].position = (t_vector){5, 6, 5};

	// sdl->lights[2].type = 1; //POINT
	// sdl->lights[2].intensity = 0.45;
	// sdl->lights[2].position = (t_vector){2, 3, -5};
	// /////////////////////////////////////////////////////////////////
}

double	*hit_sphere(t_ray *ray, t_shape *shape)
{
	t_vector oc;
	double	a;
	double	b;
	double	c;
	double	disc;
	double	*xs;

	xs = (double *)malloc(sizeof(double) * 2);
	oc = (ray->a - shape->center);
	a = dot(ray->b, ray->b);
	b = 2 * dot(oc, ray->b);
	c = dot(oc, oc) - shape->radius * shape->radius;

	disc = b * b - 4 * a * c;
	if (disc < 0)
	{
		xs[0] = MAX_I;
		xs[1] = MAX_I;
		return (xs);
	}
	xs[0] = (-b + sqrt(disc)) / (2.0 * a);
	xs[1] = (-b - sqrt(disc)) / (2.0 * a);
	return (xs);
}

double		hit_plane(t_ray *ray, t_shape *shape)
{
	t_vector	oc;
	double		a;
	double		b;
	double		result;

	oc = ray->a - shape->center;
	a = -(dot(oc, shape->axis_v));
	b = dot(ray->b, shape->axis_v);
	if (b == 0)
		return (-1.0);
	result = a / b;
	return (result);
}

double		*hit_cylinder(t_ray *ray, t_shape *shape)
{
	t_vector	oc;
	double		*xs;
	double		a;
	double		b;
	double		c;
	double		disc;

	xs = (double *)malloc(sizeof(double) * 2);
	oc = ray->a - shape->center;
	a = dot(ray->b, ray->b) - pow(dot(ray->b, shape->axis_v), 2);
	b = 2 * (dot(ray->b, oc) -  (dot(ray->b, shape->axis_v) * dot(oc, shape->axis_v)));
	c = dot(oc, oc) - pow(dot(oc, shape->axis_v), 2) - shape->radius * shape->radius;

	disc = b * b - 4 * a * c;
	if (disc < 0)
	{
		xs[0] = MAX_I;
		xs[1] = MAX_I;
		return (xs);
	}
	xs[0] = (-b + sqrt(disc)) / (2.0 * a);
	xs[1] = (-b - sqrt(disc)) / (2.0 * a);
	return (xs);
}

double		*hit_cone(t_ray *ray, t_shape *shape)
{
	t_vector	oc;
	double		*xs;
	double		a;
	double		b;
	double		c;
	double		e;
	double		disc;

	xs = (double *)malloc(sizeof(double) * 2);
	oc = ray->a - shape->center;
	e = (1 + pow(sin(DEG * shape->angle) / cos(DEG * shape->angle), 2));
	a = dot(ray->b, ray->b) - e * pow(dot(ray->b, shape->axis_v), 2);
	b = 2 * (dot(ray->b, oc) - e * (dot(ray->b, shape->axis_v) * dot(oc, shape->axis_v)));
	c = dot(oc, oc) - e * (pow(dot(oc, shape->axis_v), 2));

	disc = b * b - 4 * a * c;
	if (disc < 0)
	{
		xs[0] = MAX_I;
		xs[1] = MAX_I;
		return (xs);
	}
	xs[0] = (-b + sqrt(disc)) / (2.0 * a);
	xs[1] = (-b - sqrt(disc)) / (2.0 * a);
	return (xs);
}

t_shape		ClosestIntersaction(t_sdl *sdl, t_ray *ray, double min_t, double max_t)
{
	double		closest_t = MAX_I;
	int			hit = 0;
	double		*ts;
	double		a;	
	t_shape		closest_shape;
	t_shape		*tmp;
	int			i = 0;

	//closest_shape = (t_shape *)malloc(sizeof(t_shape));
	tmp = sdl->shapes;
	while (tmp/*i < 7*/) //tmp = sdl->shapes[i].type
	{
		if (tmp->type == 1 || tmp->type == 3 || tmp->type == 4)
		{
			if (tmp->type == 1)
				ts = hit_sphere(ray, tmp);
			else if (tmp->type == 3)
				ts = hit_cylinder(ray, tmp);
			else
				ts = hit_cone(ray, tmp);
			if (ts[0] < closest_t && min_t < ts[0] && ts[0] < max_t)
			{
				closest_t = ts[0];
				closest_shape = *tmp;
				hit = 1;
			}
			if (ts[1] < closest_t && min_t < ts[1] && ts[1] < max_t)
			{
				closest_t = ts[1];
				closest_shape = *tmp;
				hit = 1;
			}
			free(ts);
		}
		else if (tmp->type == 2)
		{
			a = hit_plane(ray, tmp);  
			if (a < closest_t && min_t < a && a < max_t)
			{
				closest_t = a;
				closest_shape = *tmp;
				hit = 1;
			}
		}
		//i++;
		tmp = tmp->next;
	}
	if (hit == 1)
		closest_shape.clos_t = closest_t;
	else
		closest_shape.clos_t = -1.0;
	return (closest_shape);
}

double			ComputeLighting(t_sdl *sdl, t_vector point, t_vector normal, t_vector view, int s)
{
	double		intensity = 0.0;
	double		length = v_length(normal);
	int			i = 0;
	t_light		*light;
	t_vector	vec_l;
	t_vector	vec_r;
	double		n_dot_l;
	double		r_dot_v; 
	double		t_max = 0.0;
	t_shape		shape;
	t_ray		*tmp_ray;

	//shape = (t_shape *)nalloc(sizeof(t_shape));
	tmp_ray = (t_ray *)malloc(sizeof(t_ray)); // Виправити це і замінити на щось адекватне!!!!
	light = sdl->lights;
	while (light)
	{
		if (light->type == 0)
			intensity += light->intensity;
		else
		{
			vec_l = light->position - point;
			t_max = 1.0;
			tmp_ray->a = point;
			tmp_ray->b = vec_l;
			shape = ClosestIntersaction(sdl, tmp_ray, 0.00001, t_max);
			if (shape.clos_t == -1.0)
			{	
				n_dot_l = dot(normal, vec_l);
				if (n_dot_l > 0)
					intensity += light->intensity * n_dot_l / (length * v_length(vec_l));

				if (s > -1)
				{
					vec_r = (v_multi(2.0 * dot(normal, vec_l), normal) - vec_l);
					r_dot_v = dot(vec_r, view);
					if (r_dot_v > 0)
						intensity += light->intensity * pow(r_dot_v / (v_length(vec_r) * v_length(view)), (double)s);
				}
			}
		}
		light = sdl->lights->next;
	}
	free(tmp_ray);
	return (intensity);
}

t_vector	TraceRay(t_sdl *sdl, t_ray *ray, double min_t, double max_t)
{
	t_vector	point;
	t_vector	normal;
	t_vector	view;
	t_shape		closest_shape;
	double		light_power;
	
	closest_shape = ClosestIntersaction(sdl, sdl->ray, min_t, max_t);
	if (closest_shape.clos_t == -1.0)
		return (sdl->background);

	point = point_vector(closest_shape.clos_t, ray);
	if (closest_shape.type == 1)
		normal = unit_vector(point - closest_shape.center);
	else if (closest_shape.type == 2)
	{
		if (dot(ray->b, closest_shape.axis_v) < 0)
			normal = closest_shape.axis_v;
		else
			normal = -closest_shape.axis_v;
	}
	else if (closest_shape.type == 3)
	{
		normal = unit_vector(point - closest_shape.center - v_multi((dot(ray->b, closest_shape.axis_v) *
			closest_shape.clos_t +  dot(ray->a - closest_shape.center, closest_shape.axis_v)), closest_shape.axis_v));
	}
	else if (closest_shape.type == 4)
	{
		normal = unit_vector(point - closest_shape.center - v_multi((1 + pow(sin(closest_shape.angle * DEG) / cos(closest_shape.angle * DEG), 2)) *
			(dot(ray->b, closest_shape.axis_v) * closest_shape.clos_t + dot(ray->a - closest_shape.center, closest_shape.axis_v)), closest_shape.axis_v));
	}
	view = v_multi(-1, ray->b);
	light_power = ComputeLighting(sdl, point, normal, view, closest_shape.specular);
	return (v_multi(light_power, closest_shape.color));
}

int			draw(t_sdl *sdl)
{
	int sdl_color = 0;
	int i = -WDTH / 2;
	int j;
	t_vector col;
	double u;
	double v;

	while (i < WDTH / 2)
	{
		j = -HGHT / 2;
		while (j < HGHT / 2)
		{
			u = i * sdl->x_unit;
			v = j * sdl->y_unit;
			sdl->ray->b = (t_vector){u, v, sdl->projection_plane_z}; 
			sdl->ray->b = unit_vector(rot(sdl->ray->b, sdl));
			col = Check_colors(TraceRay(sdl, sdl->ray, 1, MAX_I));
			sdl_color = SDL_MapRGB(sdl->surf->format, col[0], col[1], col[2]);
			((int *)sdl->surf->pixels)[(HGHT / 2 - j - 1) * WDTH + (WDTH / 2 + i)] = sdl_color; // Видалити "-1" якщо не працює
			j++;
		}
		i++;
	}
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
	/*SDL_DestroyWindow(sdl->win);
	SDL_Quit();*/
	return (0);
}
