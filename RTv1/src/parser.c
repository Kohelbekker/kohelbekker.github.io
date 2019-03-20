/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 18:43:29 by aperesad          #+#    #+#             */
/*   Updated: 2019/03/07 18:43:30 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void			get_scene(t_sdl *sdl, int fd)
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
		a++;
	}
	if (a == 0)
		error(sdl, "Empty file!\n");
}

void			check_first_line(t_sdl *sdl, char *str)
{
	int			i;
	char		**line;

	i = 1;
	line = ft_strsplit(str, ' ');
	if ((strcmp(line[0], "camera:") != 0) || (row_nbr(line) != 3))
		error(sdl, "Error, empty file, or incorrect first line!"
			" (please, use only lowercase letters)\n");
	else
	{
		while (i < 3)
		{
			set_cam(sdl, i, line);
			i++;
		}
	}
	free_str(line);
}

void			get_shape(t_sdl *sdl, char *str)
{
	char		**tmp;

	tmp = ft_strsplit(str, ' ');
	if (row_nbr(tmp) < 3)
		error(sdl, "Error. Please, don't use unnecessary signs, spaces \
		and empty lines!\n");
	if (strcmp(tmp[0], "sphere:") == 0)
		set_sphere(sdl, tmp, 1);
	else if (strcmp(tmp[0], "plane:") == 0)
		set_plane(sdl, tmp, 1);
	else if (strcmp(tmp[0], "cylinder:") == 0)
		set_cylinder(sdl, tmp, 1);
	else if (strcmp(tmp[0], "cone:") == 0)
		set_cone(sdl, tmp, 1);
	else if (strcmp(tmp[0], "light:") == 0)
		set_light(sdl, tmp, 1);
	else
	{
		free_str(tmp);
		error(sdl, "Error. File contains wrong symbols or additional lines");
	}
	free_str(tmp);
}

void			set_cam(t_sdl *sdl, int i, char **line)
{
	char		**word;
	char		*str;
	int			*vec;

	if (line[i][0] != '(' || line[i][last_char(line[i])] != ')')
		error(sdl, "Errror, use '(' & ')' for every separate argument\n");
	str = ft_strsub(line[i], 1, last_char(line[i]) - 1);
	word = ft_strsplit(str, ',');
	if (row_nbr(word) != 3)
		error(sdl, "Wrong amount of coordinates!\n");
	vec = check_cycle(sdl, 0, 0, word);
	if (i == 1)
		sdl->ray->a = int_to_vec(vec, 10.0);
	else
		sdl->cam_rot = int_to_vec(vec, 1.0);
	free(str);
	free(vec);
	free_str(word);
}
