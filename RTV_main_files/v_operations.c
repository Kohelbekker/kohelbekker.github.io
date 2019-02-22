#include "new_RTv1.h"

t_sdl		*sdl_clean(t_sdl *sdl)
{
	if (sdl->win != NULL)
		SDL_DestroyWindow(sdl->win);
	free(sdl->ray);
	SDL_Quit();
	// system("leaks a.out -q");
	return (0);
}

/*t_shape		*ft_lstadd_shape(t_sdl *sdl, t_shape *new)
{
	t_shape		*head;

	head = sdl->shapes;
	if (sdl->shapes == NULL)
	{
		printf("here\n");
		sdl->shapes->next = NULL;
		return	(new);
	}
	while (sdl->shapes->next != NULL)
		sdl->shapes = sdl->shapes->next; 
	sdl->shapes->next = new;
	sdl->shapes = sdl->shapes->next;
	printf("there\n");
	sdl->shapes->next = NULL;
	return (head);
}

t_light			*ft_lstadd_light(t_sdl *sdl, t_light *new)
{
	t_light		*head;

	head = sdl->lights;
	if (sdl->lights == NULL)
		return	(new);
	while (sdl->lights->next != NULL)
		sdl->lights = sdl->lights->next; 
	sdl->lights->next = new;
	return (head);
}*/

t_vector	v_multi(double a, t_vector b)
{
	t_vector tmp = (t_vector){a, a, a};
	return (tmp * b); 
}

double		v_length(t_vector a)
{
	return (sqrt((double)(a[0] * a[0] + a[1] * a[1] + a[2] * a[2])));
}

int			av_check(char *av)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 3;
	str = (char *)malloc(sizeof(char) * 5);
	str[4] = '\0';
	while (av[i])
		i++;
	i--;
	while (j > -1)
	{
		str[j] = av[i];
		j--;
		i--;
	}
	if (strcmp(str, ".rtv") == 0)
	{
		free(str);
		return (1);
	}
	free(str);
	return (0);
}

t_vector	unit_vector(t_vector b) // Відбувається нормалізація вектора, тобто приведення до ветокра колінеарного початковому, але з довжиною 1
{
	return (v_div(v_length(b), b));
}

t_vector	point_vector(double f, t_ray *ray)
{
	t_vector i;

	i = v_multi(f, ray->b);
	return (ray->a + i);
}

void		zero_error(char *str)
{
	ft_putendl(str);
	exit(1);
}

void		error(t_sdl *sdl, char *str)
{
	t_shape	 *tmp;

	if (sdl->win != NULL)
		SDL_DestroyWindow(sdl->win);
	if (sdl->shapes != NULL)
	{
		while (sdl->shapes)
		{
			tmp = sdl->shapes->next;
			free(sdl->shapes);
			sdl->shapes = tmp;
		}
	}
	//free(sdl);
	ft_putendl(str);
	SDL_Quit();
	exit(1);
}

double		dot(t_vector a, t_vector b)
{
	return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
}

t_vector	Check_colors(t_vector col)
{
	col[0] = MIN(255, MAX(0, (int)col[0]));
	col[1] = MIN(255, MAX(0, (int)col[1]));
	col[2] = MIN(255, MAX(0, (int)col[2]));
	return (col);
}

t_vector	v_div(double b, t_vector a)
{
	t_vector	tmp;

	tmp = (t_vector){b, b, b};

	return (a / tmp);
}

// t_vector	v_add(t_vector a, double b)
// {
// 	t_vector	tmp;

// 	tmp = (t_vector){b, b, b};
// 	return (a + tmp);
// }