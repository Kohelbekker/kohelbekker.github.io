/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 18:49:30 by aperesad          #+#    #+#             */
/*   Updated: 2019/03/07 18:49:41 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void		light_intens(t_sdl *sdl, t_light *tmp, char **word)
{
	int		a;
	int		j;

	j = 0;
	if (row_nbr(word) != 1)
		error(sdl, "Wrong amount of arguments for intensity\n");
	while (word[0][j])
	{
		if (word[0][0] == '-')
			error(sdl, "please, use positive values for light intensity!\n");
		if (!(ft_isdigit(word[0][j])))
			error(sdl, "Error, non-digit values, please use only int!\n");
		j++;
	}
	a = ft_atoi(word[0]);
	if (a < 0 || a > 100)
		error(sdl, "Please, use digits between 0 and 100 to set intensity\n");
	tmp->intensity = ((double)a / 100.0);
}

void		light_type(t_sdl *sdl, t_light *tmp, char **word)
{
	int		a;
	int		j;

	j = 0;
	if (row_nbr(word) != 1)
		error(sdl, "Wrong amount of arguments for radius setting\n");
	while (word[0][j])
	{
		if (!(ft_isdigit(word[0][j])))
			error(sdl, "Error, non-digit values, please use only int!\n");
		j++;
	}
	a = ft_atoi(word[0]);
	if (a == 0)
		tmp->type = 0;
	else if (a == 1)
		tmp->type = 1;
	else
		error(sdl, "Please, choose light type 1 or 0\n");
}

void		light_center(t_sdl *sdl, t_light *tmp, char **word)
{
	int		*vec;

	if (row_nbr(word) != 3)
		error(sdl, "Wrong amount of arguments for light setting\n");
	vec = check_cycle(sdl, 0, 0, word);
	tmp->position = int_to_vec(vec, 10.0);
	free(vec);
}
