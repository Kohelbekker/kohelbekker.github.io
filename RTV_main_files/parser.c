#include "new_RTv1.h"

int				*check_cycle(t_sdl *sdl, int j, int a, char **word)
{
	static int			vec[3];

	while (j < 3)
	{
		while (word[j][a])
		{
			if (!(ft_isdigit(word[j][a])))
				error(sdl, "Error, non-digit values, please use only integers!\n");
			a++;
		}
		vec[j] = ft_atoi(word[j]);
		j++;
		a = 0; 
	}
	return (vec);
}

void			light_intens(t_sdl *sdl, t_light *tmp, char **word)
{
	int		a;
	int		j;

	j = 0;
	if (row_nbr(word) != 1)
		error(sdl, "Wrong amount of arguments for radius setting\n");
	while (word[0][j])
	{
		if (!(ft_isdigit(word[0][j])))
				error(sdl, "Error, non-digit values, please use only integers!\n");
		j++;
	}
	a = ft_atoi(word[0]);
	if (a < 0 || a > 100)
		error(sdl, "Please, use digits between 0 and 100 to set intensity\n");
	tmp->intensity = ((double)a / 100.0);
}

void			light_type(t_sdl *sdl, t_light *tmp, char **word)
{
	int		a;
	int		j;

	j = 0;
	if (row_nbr(word) != 1)
		error(sdl, "Wrong amount of arguments for radius setting\n");
	while (word[0][j])
	{
		if (!(ft_isdigit(word[0][j])))
				error(sdl, "Error, non-digit values, please use only integers!\n");
		j++;
	}
	a = ft_atoi(word[0]);
	if (a == 0)
		tmp->type = 0;
	if (a == 1)
		tmp->type = 1;
	else
		error(sdl, "Please, choose light type 1 or 0\n");
}

void			light_center(t_sdl *sdl, t_light *tmp, char **word)
{
	int		*vec;

	if (row_nbr(word) != 3)
		error(sdl, "Wrong amount of arguments for light setting\n");
	vec = check_cycle(sdl, 0, 0, word);
	tmp->position = int_to_vec(vec, 10.0);
}

void			shape_center(t_sdl *sdl, t_shape *tmp, char **word)
{
	int		*vec;

	if (row_nbr(word) != 3)
		error(sdl, "Wrong amount of arguments for center setting\n");
	vec = check_cycle(sdl, 0, 0, word);
	tmp->center = int_to_vec(vec, 10.0);
}

void			shape_axis(t_sdl *sdl, t_shape *tmp, char **word)
{
	int		*vec;

	int i = 0;

	if (row_nbr(word) != 3)
		error(sdl, "Wrong amount of arguments for axis setting\n");
	vec = check_cycle(sdl, 0, 0, word);
	tmp->axis_v = int_to_vec(vec, 1.0);
	tmp->axis_v = unit_vector(tmp->axis_v);
}

void			shape_radius(t_sdl *sdl, t_shape *tmp, char **word)
{
	int		a;
	int		j;

	j = 0;
	if (row_nbr(word) != 1)
		error(sdl, "Wrong amount of arguments for radius setting\n");
	while (word[0][j])
	{
		if (!(ft_isdigit(word[0][j])))
				error(sdl, "Error, non-digit values, please use only integers!\n");
		j++;
	}
	a = ft_atoi(word[0]);
	tmp->radius = ((double)a / 10.0);
}

void			shape_angle(t_sdl *sdl, t_shape *tmp, char **word)
{
	int		a;
	int		j;

	j = 0;
	if (row_nbr(word) != 1)
		error(sdl, "Wrong amount of arguments for radius setting\n");
	while (word[0][j])
	{
		if (!(ft_isdigit(word[0][j])))
				error(sdl, "Error, non-digit values, please use only integers!\n");
		j++;
	}
	a = ft_atoi(word[0]);
	if (a < 0 || a > 180)
		error(sdl, "Please, use valid amount of degrees for angle (from 0 to 180)\n");
	tmp->angle = (double)a;
}

void			shape_color(t_sdl *sdl, t_shape *tmp, char **word)
{
	int		*vec;
	int		j;

	j = 0;
	if (row_nbr(word) != 3)
		error(sdl, "Wrong amount of arguments for center setting\n");
	vec = check_cycle(sdl, 0, 0, word);
	while (j < 3)
	{
		if (vec[j] > 255 || vec[j] < 0)
			error(sdl, "Please, use numbers between 0 and 255 to set color\n");
		j++;
	}
	tmp->color = int_to_vec(vec, 1.0);
}

void			shape_specular(t_sdl *sdl, t_shape *tmp, char **word)
{
	int		a;
	int		j;

	j = 0;
	if (row_nbr(word) != 1)
		error(sdl, "Wrong amount of arguments for specular setting\n");
	while (word[0][j])
	{
		if (!(ft_isdigit(word[0][j])))
				error(sdl, "Error, non-digit values, please use only integers!\n");
		j++;
	}
	a = ft_atoi(word[0]);
	if (a < -1 || a > 1000)
		error(sdl, "Please, use numbers between -1 and 1000 to set specular\n");
	tmp->specular =  a;
}

t_shape			*set_sphere(t_sdl *sdl, char **line, int i)
{
	char		**word;
	char		*str;
	t_shape		*tmp;
	t_shape		*head;

	if (sdl->shapes)
		head = sdl->shapes;
	else
		head = NULL;
	if (row_nbr(line) != 5)
		error (sdl, "Wrong amount of arguments for sphere!\n");
	tmp = (t_shape *)malloc(sizeof(t_shape));
	tmp->type = 1;

	while (i < 5)
	{
		if (line[i][0] != '(' || line[i][last_char(line[i])] != ')')
			error (sdl, "Errror, use '(' & ')' for every separate argument\n");
		str = ft_strsub(line[i], 1, last_char(line[i]) - 1);
		word = ft_strsplit(str, ',');
		if (i == 1)
			shape_center(sdl, tmp, word);
		else if (i == 2)
			shape_radius(sdl, tmp, word);
		else if (i == 3)
			shape_color(sdl, tmp, word);
		else
			shape_specular(sdl, tmp, word);
		ft_strdel(word);
		free(str);
		i++;
	}
	tmp->next = NULL;
	/*printf("tmp->type = %d\n", tmp->type);
	printf("center = %f, %f, %f\n", tmp->center[0], tmp->center[1], tmp->center[2]);
	printf("specular = %d\n", tmp->specular);*/
	if (head == NULL)
	{
		sdl->shapes = tmp;

		printf("no first list\n");
	}
	else
	{
		printf("just mobve forward\n");
		printf("{%d}\n", sdl->shapes->type);
		while (sdl->shapes->next)
			sdl->shapes = sdl->shapes->next;
		sdl->shapes->next = tmp;
		sdl->shapes = head;
	}

	//sdl->shapes = ft_lstadd_shape(sdl, tmp);
	printf("kek\n");
	// printf("2tmp->type = %d\n", head->type);
	// printf("2center = %f, %f, %f\n", head->center[0], head->center[1], head->center[2]);
	// printf("2specular = %d\n", head->specular);
	i = 0;
	
	free(word);
	return(sdl->shapes);
}

t_shape			*set_plane(t_sdl *sdl, char **line, int i)
{
	char		**word;
	char		*str;
	t_shape		*tmp;
	t_shape		*head;

	if (sdl->shapes)
		head = sdl->shapes;
	else
		head = NULL;

	if (row_nbr(line) != 5)
		error (sdl, "Wrong amount of arguments for plane!\n");
	tmp = (t_shape *)malloc(sizeof(t_shape));
	tmp->next = NULL;
	tmp->type = 2;
	while (i < 5)
	{
		if (line[i][0] != '(' || line[i][last_char(line[i])] != ')')
			error (sdl, "Errror, use '(' & ')' for every separate argument\n");
		str = ft_strsub(line[i], 1, last_char(line[i]) - 1);
		word = ft_strsplit(str, ',');
		if (i == 1)
			shape_center(sdl, tmp, word);
		else if (i == 2)
			shape_axis(sdl, tmp, word);
		else if (i == 3)
			shape_color(sdl, tmp, word);
		else
			shape_specular(sdl, tmp, word);
		i++;
		free(str);
		ft_strdel(word);
	}
	if (sdl->shapes == NULL)
	{
		sdl->shapes = tmp;
		sdl->shapes->next = NULL;
	}
	else
	{
		t_shape		*head;

		head = sdl->shapes;
		while (sdl->shapes->next != NULL)
			sdl->shapes = sdl->shapes->next;
		sdl->shapes->next = tmp;
		sdl->shapes = head;
	}
	//sdl->shapes = ft_lstadd_shape(sdl, tmp);
	i = 0;
	while (word[i])
	{
		free(word[i]);
		i++;
	}
	free(word);
	return(sdl->shapes);
}

t_shape			*set_cylinder(t_sdl *sdl, char **line, int i)
{
	char		**word;
	t_shape		*tmp;
	char *str;
	t_shape		*head;

	if (sdl->shapes)
		head = sdl->shapes;
	else
		head = NULL;

	if (row_nbr(line) != 6)
		error (sdl, "Wrong amount of arguments for cylinder!\n");
	tmp = (t_shape *)malloc(sizeof(t_shape));
	tmp->next = NULL;
	tmp->type = 3;
	while (i < 6)
	{
		if (line[i][0] != '(' || line[i][last_char(line[i])] != ')')
			error (sdl, "Errror, use '(' & ')' for every separate argument\n");
		str = ft_strsub(line[i], 1, last_char(line[i]) - 1);
		word = ft_strsplit(str, ',');
		if (i == 1)
			shape_center(sdl, tmp, word);
		else if (i == 2)
			shape_axis(sdl, tmp, word);
		else if (i == 3)
			shape_color(sdl, tmp, word);
		else if (i == 4)
			shape_radius(sdl, tmp, word);
		else
			shape_specular(sdl, tmp, word);
		i++;
		ft_strdel(word);
		free(str);
	}
	if (sdl->shapes == NULL)
	{
		sdl->shapes = tmp;
		sdl->shapes->next = NULL;
	}
	else
	{
		t_shape		*head;

		head = sdl->shapes;
		while (sdl->shapes->next != NULL)
			sdl->shapes = sdl->shapes->next;
		sdl->shapes->next = tmp;
		sdl->shapes = head;
	}
	//sdl->shapes = ft_lstadd_shape(sdl, tmp);
	
	return(sdl->shapes);
}

t_shape			*set_cone(t_sdl *sdl, char **line, int i)
{
	char		**word;
	t_shape		*tmp;
	t_shape		*head;
	char 	*str;

	if (sdl->shapes)
		head = sdl->shapes;
	else
		head = NULL;

	if (row_nbr(line) != 6)
		error (sdl, "Wrong amount of arguments for cylinder!\n");
	tmp = (t_shape *)malloc(sizeof(t_shape));
	tmp->next = NULL;
	tmp->type = 4;
	while (i < 6)
	{
		if (line[i][0] != '(' || line[i][last_char(line[i])] != ')')
			error (sdl, "Errror, use '(' & ')' for every separate argument\n");
		str = ft_strsub(line[i], 1, last_char(line[i]) - 1);
		word = ft_strsplit(str, ',');
		if (i == 1)
			shape_center(sdl, tmp, word);
		else if (i == 2)
			shape_axis(sdl, tmp, word);
		else if (i == 3)
			shape_color(sdl, tmp, word);
		else if (i == 4)
			shape_angle(sdl, tmp, word);
		else
			shape_specular(sdl, tmp, word);
		i++;
		ft_strdel(word);
		free(str);
	}
	if (sdl->shapes == NULL)
	{
		sdl->shapes = tmp;
		sdl->shapes->next = NULL;
	}
	else
	{
		t_shape		*head;

		head = sdl->shapes;
		while (sdl->shapes->next != NULL)
			sdl->shapes = sdl->shapes->next;
		sdl->shapes->next = tmp;
		sdl->shapes = head;
	}
	//sdl->shapes = ft_lstadd_shape(sdl, tmp);
	
	return(sdl->shapes);
}

t_light			*set_light(t_sdl *sdl, char **line, int i)
{
	char		**word;
	t_light		*tmp;
	t_light		*head;
	char *str;

	if (sdl->lights)
		head = sdl->lights;
	else
		head = NULL;

	if (row_nbr(line) != 4)
		error (sdl, "Wrong amount of arguments for plane!\n");
	tmp = (t_light *)malloc(sizeof(t_light));
	tmp->next = NULL;
	while (i < 4)
	{
		if (line[i][0] != '(' || line[i][last_char(line[i])] != ')')
			error (sdl, "Errror, use '(' & ')' for every separate argument\n");
		str = ft_strsub(line[i], 1, last_char(line[i]) - 1);
		word = ft_strsplit(str, ',');
		if (i == 1)
			light_center(sdl, tmp, word);
		else if (i == 2)
			light_intens(sdl, tmp, word);
		else
			light_type(sdl, tmp, word);
		i++;
		ft_strdel(word);
		free(str);
	}
	if (sdl->lights == NULL)
	{
		sdl->lights = tmp;
		sdl->lights->next = NULL;
	}
	else
	{
		t_light		*head;

		head = sdl->lights;
		while (sdl->lights->next != NULL)
			sdl->lights = sdl->lights->next;
		sdl->lights->next = tmp;
		sdl->lights = head;
	}
	//sdl->lights = ft_lstadd_light(sdl, tmp);

	return(sdl->lights);
}

void			get_shape(t_sdl *sdl, char *str)
{
	char		**tmp;

	printf("GETTING SHAPE!\n");
	tmp = ft_strsplit(str, ' ');
	if (row_nbr(tmp) < 3)
		error (sdl, "Error. Please, don't use unnecessary signs, spaces \
		 and empty lines!\n");
	if (strcmp(tmp[0], "sphere:") == 0)
	{
		sdl->shapes = set_sphere(sdl, tmp, 1);
		
	}
	else if (strcmp(tmp[0], "plane:") == 0)
		sdl->shapes = set_plane(sdl, tmp, 1);
	else if (strcmp(tmp[0], "cylinder:") == 0)
		sdl->shapes = set_cylinder(sdl, tmp, 1);
	else if (strcmp(tmp[0], "cone:") == 0)
		sdl->shapes = set_cone(sdl, tmp, 1);
	else if (strcmp(tmp[0], "light:") == 0)
		sdl->lights = set_light(sdl, tmp, 1);
	else
		error (sdl, "Error. File contains wrong symbols or additional lines");

	int i = 0;
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
}

int				last_char(char *str)
{
	int			i;

	i = 0;
	while (str[i])
		i++;
	i--;
	return (i);
}

int				row_nbr(char **str)
{
	int			i;
	int			j;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

t_vector		int_to_vec(int *a, double div)
{
	t_vector	vec;

	vec[0] = ((double)a[0]) / div;
	vec[1] = ((double)a[1]) / div;
	vec[2] = ((double)a[2]) / div;

	return (vec);
}

void			set_camera(t_sdl *sdl, int i, char **line, int j, int a)
{
	char		**word;
	char *str;
	int			vec[3];

	if (line[i][0] != '(' || line[i][last_char(line[i])] != ')')
		error (sdl, "Errror, use '(' & ')' for every separate argument\n");
	printf("strsub = %s\n", ft_strsub(line[i], 1, last_char(line[i]) - 1));
	str = ft_strsub(line[i], 1, last_char(line[i]) - 1);
	word = ft_strsplit(str, ',');
	if (row_nbr(word) != 3)
		error (sdl, "Wrong amount of coordinates!\n");
	while (j < 3)
	{
		while (word[j][a])
		{
			if (!(ft_isdigit(word[j][a])))
				error(sdl, "Error, non-digit values, please use only integers!\n");
			a++;
		}
		vec[j] = ft_atoi(word[j]);
		j++;
		a = 0; 
	}
	if (i == 1)
		sdl->ray->a = int_to_vec(vec, 10.0);
	else
		sdl->cam_rot = int_to_vec(vec, 1.0);
	
	free(str);
	ft_strdel(word);
}

void				check_first_line(t_sdl *sdl, char *str)
{
	int			i;
	char		**line;

	i = 1;
	line = ft_strsplit(str, ' ');
	if ((strcmp(line[0], "camera:") != 0) || (row_nbr(line) != 3))
		error(sdl, "Error, empty file, or incorrect first line! \
			(please, use only lowercase letters)\n");
	else
	{
		while (i < 3)
		{
			set_camera(sdl, i, line, 0, 0);
			i++;
		}
	}
	

	i = 0;
	while (line[i])
	{
		free(line[i]);
		i++;
	}
	free(line);
}

void				get_scene(t_sdl *sdl, char *av, int fd)
{
	int			a;
	char		*str;

	a = 0;
	while (get_next_line(fd, &str))
	{
		if (a == 0)
			check_first_line(sdl, str);
		else
			get_shape(sdl, str);
		free(str);
		printf("a=  %d\n", a);
		a++;
	}
	system("leaks a.out -q");
	printf ("sdl->type = %d\n", sdl->shapes->type);
	/////////////////////////////////////////////////////////////
/*	t_shape		*tmp = sdl->shapes;
	while (tmp != NULL)
	{
		printf("shape-type = %d\n", tmp->type);
		tmp = tmp->next;
	}*/
	
	/////////////////////////////////////////////////////////////
}