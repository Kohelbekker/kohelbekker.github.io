/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_shape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 18:38:09 by aperesad          #+#    #+#             */
/*   Updated: 2019/03/07 18:38:12 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void			set_sphere(t_sdl *sdl, char **line, int i)
{
	char		**word;
	char		*str;
	t_shape		*tmp;

	if (row_nbr(line) != 5)
		error(sdl, "Wrong amount of arguments for sphere!\n");
	tmp = (t_shape *)malloc(sizeof(t_shape));
	tmp->type = 1;
	while (i < 5)
	{
		if (line[i][0] != '(' || line[i][last_char(line[i])] != ')')
			error(sdl, "Errror, use '(' & ')' for every separate argument\n");
		str = ft_strsub(line[i], 1, last_char(line[i]) - 1);
		word = ft_strsplit(str, ',');
		param1(sdl, tmp, word, i);
		free_str(word);
		free(str);
		i++;
	}
	tmp->next = NULL;
	sdl->shapes = add_list(sdl, tmp);
}

void			set_plane(t_sdl *sdl, char **line, int i)
{
	char		**word;
	char		*str;
	t_shape		*tmp;

	if (row_nbr(line) != 4)
		error(sdl, "Wrong amount of arguments for plane!\n");
	tmp = (t_shape *)malloc(sizeof(t_shape));
	tmp->next = NULL;
	tmp->type = 2;
	while (i < 4)
	{
		if (line[i][0] != '(' || line[i][last_char(line[i])] != ')')
			error(sdl, "Errror, use '(' & ')' for every separate argument\n");
		str = ft_strsub(line[i], 1, last_char(line[i]) - 1);
		word = ft_strsplit(str, ',');
		param2(sdl, tmp, word, i);
		i++;
		free(str);
		free_str(word);
	}
	tmp->specular = -1;
	sdl->shapes = add_list(sdl, tmp);
}

void			set_cylinder(t_sdl *sdl, char **line, int i)
{
	char		**word;
	t_shape		*tmp;
	char		*str;

	if (row_nbr(line) != 6)
		error(sdl, "Wrong amount of arguments for cylinder!\n");
	tmp = (t_shape *)malloc(sizeof(t_shape));
	tmp->next = NULL;
	tmp->type = 3;
	while (i < 6)
	{
		if (line[i][0] != '(' || line[i][last_char(line[i])] != ')')
			error(sdl, "Errror, use '(' & ')' for every separate argument\n");
		str = ft_strsub(line[i], 1, last_char(line[i]) - 1);
		word = ft_strsplit(str, ',');
		param4(sdl, tmp, word, i);
		i++;
		free_str(word);
		free(str);
	}
	sdl->shapes = add_list(sdl, tmp);
}

void			set_cone(t_sdl *sdl, char **line, int i)
{
	char		**word;
	t_shape		*tmp;
	char		*str;

	if (row_nbr(line) != 6)
		error(sdl, "Wrong amount of arguments for cylinder!\n");
	tmp = (t_shape *)malloc(sizeof(t_shape));
	tmp->next = NULL;
	tmp->type = 4;
	while (i < 6)
	{
		if (line[i][0] != '(' || line[i][last_char(line[i])] != ')')
			error(sdl, "Errror, use '(' & ')' for every separate argument\n");
		str = ft_strsub(line[i], 1, last_char(line[i]) - 1);
		word = ft_strsplit(str, ',');
		param3(sdl, tmp, word, i);
		i++;
		free_str(word);
		free(str);
	}
	sdl->shapes = add_list(sdl, tmp);
}

void			set_light(t_sdl *sdl, char **line, int i)
{
	char		**word;
	t_light		*tmp;
	char		*str;

	if (row_nbr(line) != 4)
		error(sdl, "Wrong amount of arguments for light!\n");
	tmp = (t_light *)malloc(sizeof(t_light));
	tmp->next = NULL;
	while (i < 4)
	{
		if (line[i][0] != '(' || line[i][last_char(line[i])] != ')')
			error(sdl, "Errror, use '(' & ')' for every separate argument\n");
		str = ft_strsub(line[i], 1, last_char(line[i]) - 1);
		word = ft_strsplit(str, ',');
		if (i == 1)
			light_center(sdl, tmp, word);
		else if (i == 2)
			light_intens(sdl, tmp, word);
		else if (i == 3)
			light_type(sdl, tmp, word);
		i++;
		free_str(word);
		free(str);
	}
	sdl->lights = add_light(sdl, tmp);
}
