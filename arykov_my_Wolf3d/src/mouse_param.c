/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arykov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 14:00:59 by arykov            #+#    #+#             */
/*   Updated: 2018/11/30 14:13:04 by arykov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	change_map(t_box *box)
{
	if (box->start == 1)
	{
		box->pic->this_pic = box->pic->this_picm0;
		SDL_UpdateWindowSurface(box->wind);
	}
	if (box->start == 2)
	{
		box->pic->this_pic = box->pic->this_picm1;
		SDL_UpdateWindowSurface(box->wind);
	}
	if (box->start == 3)
	{
		box->pic->this_pic = box->pic->this_picm2;
		SDL_UpdateWindowSurface(box->wind);
	}
	if (box->start == 0)
	{
		box->pic->this_pic = box->pic->this_picbm;
		SDL_UpdateWindowSurface(box->wind);
		//error_msg(box);
	}
}

int		menu_mouse(int code, int x, int y, t_box *box)
{
	if (code == SDL_BUTTON_LEFT && box->error == 0)
	{
		if ((x > 1030 && x < 1140) && (y > 62 && y < 105))
		{
			box->start = 1;
			change_map(box);
		}
		if ((x > 1030 && x < 1140) && (y > 120 && y < 160))
		{
			box->start = 2;
			change_map(box);
		}
		if ((x > 1030 && x < 1140) && (y > 174 && y < 215))
		{
			box->start = 3;
			change_map(box);
		}
		if ((x > 565 && x < 710) && (y > 470 && y < 520))
			exit_this();
		menu_mouse_click(x, y, box);
	}
	return (0);
}

int		menu_mouse_click(int x, int y, t_box *box)
{
	if ((x > 540 && x < 738) && (y > 365 && y < 417))
	{
		if ((ft_check_all(box)) == -1)
		{
			box->start = 0;
			close(box->map_fd);
			change_map(box);
		}
		else
		{
			SDL_FreeSurface(box->surf);  //// ????????????
			close(box->map_fd);
			box->error = 1;
			box->cam.d.x = 1;
			box->cam.d.y = 0;
			box->cam.p.x = 0;
			box->cam.p.y = 0.6;
			box->go.spd = 0.05;
			lets_start_game(box);
		}
	}
	return (0);
}

/*void	error_msg(t_box *box)
{
	t_surface	*surf[8];

	if (box->error == -2)
		surf[0] = (box->mlx, box->wind, 550, 390, 0x000000,
			"NONEXISTENT MAP");
	if (box->error == -3)
		mlx_string_put(box->mlx, box->wind, 550, 390, 0x000000,
			"EMPTY MAP");
	if (box->error == -4)
		mlx_string_put(box->mlx, box->wind, 550, 390, 0x000000,
			"NON PRIME NUMBER");
	if (box->error == -5)
		mlx_string_put(box->mlx, box->wind, 550, 390, 0x000000,
			"WRONG SYMBOL");
	if (box->error == -6)
		mlx_string_put(box->mlx, box->wind, 550, 390, 0x000000,
			"MAP STRUCTURE IS INVALID");
	if (box->error == -7)
		mlx_string_put(box->mlx, box->wind, 550, 390, 0x000000,
			"MAP IS INVALID");
	if (box->error == -8)
		mlx_string_put(box->mlx, box->wind, 550, 390, 0x000000,
			"BAD SPAWN");
	if (box->error == -9)
		mlx_string_put(box->mlx, box->wind, 550, 390, 0x000000,
			"SMALL MAP");
}*/
