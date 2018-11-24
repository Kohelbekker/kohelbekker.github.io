/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 20:11:29 by aperesad          #+#    #+#             */
/*   Updated: 2018/10/24 20:11:31 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		create_texture(t_wolf *w)
{
	int i;
	int j;

	i = TEX_H;
	j = TEX_W;
	w->tex[0].img = mlx_xpm_file_to_image(w->mlx->mlx_p, "pic/s1.xpm", &i, &j);
	w->tex[1].img = mlx_xpm_file_to_image(w->mlx->mlx_p, "pic/s2.xpm", &i, &j);
	w->tex[2].img = mlx_xpm_file_to_image(w->mlx->mlx_p, "pic/s3.xpm", &i, &j);
	w->tex[3].img = mlx_xpm_file_to_image(w->mlx->mlx_p, "pic/s4.xpm", &i, &j);
	w->tex[4].img = mlx_xpm_file_to_image(w->mlx->mlx_p, "pic/fl.xpm", &i, &j);
	w->tex[5].img = mlx_xpm_file_to_image(w->mlx->mlx_p, "pic/rf.xpm", &i, &j);
	w->tex[6].img = mlx_xpm_file_to_image(w->mlx->mlx_p, "pic/s7.xpm", &i, &j);
	w->tex[7].img = mlx_xpm_file_to_image(w->mlx->mlx_p, "pic/s8.xpm", &i, &j);
	w->tex[8].img = mlx_xpm_file_to_image(w->mlx->mlx_p, "pic/s9.xpm", &i, &j);
	w->tex[9].img = mlx_xpm_file_to_image(w->mlx->mlx_p, "pic/10.xpm", &i, &j);
	w->tex[10].img = mlx_xpm_file_to_image(w->mlx->mlx_p, "pic/11.xpm", &i, &j);
	w->tex[11].img = mlx_xpm_file_to_image(w->mlx->mlx_p, "pic/12.xpm", &i, &j);
	i = 0;
	while (i < 12)
	{
		w->tex[i].data = mlx_get_data_addr(w->tex[i].img, &w->tex[i].bpp,
			&w->tex[i].sl, &w->tex[i].ed);
		w->tex[i].bpp /= 8;
		i++;
	}
}

void		texture_type(t_wolf *w)
{
	if (w->side == 0)
	{
		if ((w->step_x == -1 && w->step_y == 1) ||
			(w->step_x == -1 && w->step_y == -1))
			w->n_t = 0;
		if ((w->step_x == 1 && w->step_y == -1) ||
			(w->step_x == 1 && w->step_y == 1))
			w->n_t = 1;
	}
	else
	{
		if ((w->step_x == -1 && w->step_y == 1) ||
			(w->step_x == 1 && w->step_y == 1))
			w->n_t = 2;
		else
			w->n_t = 3;
	}
}
