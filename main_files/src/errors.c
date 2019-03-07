/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 18:34:34 by aperesad          #+#    #+#             */
/*   Updated: 2019/03/07 18:34:35 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_sdl		*sdl_clean(t_sdl *sdl)
{
	if (sdl->win != NULL)
		SDL_DestroyWindow(sdl->win);
	free(sdl->ray);
	//system("leaks a.out -q");
	SDL_Quit();
	return (0);
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
	ft_putendl(str);
	SDL_Quit();
	exit(1);
}

void		free_str(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
