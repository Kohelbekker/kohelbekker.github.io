#include "wolf3d.h"

void		lost_key(t_box *box)
{
	box->bag.n_items--;
	box->bag.posX = box->bag.posX - 50;
	if (box->bag.n_items == 3)
	{
		box->bag.posX = 105;
		box->bag.posY = box->bag.posY - 50;
	}
	box->bag.Message = NULL;
	box->bag.full_message = NULL;
}

void		health_changing(t_box *box, double x, double y)
{
	take4sprite(box, x, y);
	box->hud.hp_val = box->hud.hp_val < 75 ? box->hud.hp_val + 25 : 100;
	box->hud.rad_val = box->hud.rad_val < 20 ? 0 : box->hud.rad_val - 20;
}

void		health_pickup(t_box *box, double x, double y, double a)
{
	double	d_x;
	double	d_y;

	d_x = box->cam.d.x;
	d_y = box->cam.d.y;
	if ((box->all_map[(int)(y)][(int)(x + d_x * box->go.spd - a)]) == 2)
	{
		box->all_map[(int)(y)][(int)(x + d_x * box->go.spd - a)] = 0;
		health_changing(box, x, y);
	}
	else if ((box->all_map[(int)(y + d_y * box->go.spd + a)][(int)(x)]) == 2)
	{
		box->all_map[(int)(y + d_y * box->go.spd + a)][(int)(x)] = 0;
		health_changing(box, x, y);
	}
	else if ((box->all_map[(int)(y + d_y * box->go.spd - a)][(int)(x)]) == 2)
	{
		box->all_map[(int)(y + d_y * box->go.spd - a)][(int)(x)] = 0;
		health_changing(box, x, y);
	}
	else if ((box->all_map[(int)(y)][(int)(x + d_x * box->go.spd + a)]) == 2)
	{
		box->all_map[(int)(y)][(int)(x + d_x * box->go.spd + a)] = 0;
		health_changing(box, x, y);
	}
}

void		graal_message(t_box *box, double x, double y)
{
	double	dist_x;
	double	dist_y;

	dist_x = fabs(box->cam.d.x) > fabs(box->cam.d.y) ? box->cam.d.x : 0;
	dist_y = fabs(box->cam.d.x) <= fabs(box->cam.d.y) ? box->cam.d.y : 0;
	if (box->all_map[(int)(y + dist_y)][(int)(x + dist_x + 0.15)] == 9 &&
		box->bag.Message == NULL)
		box->bag.Message = renderText_blue("Press 'E' to end the level", 
			"ttf/mainfont.ttf", 22, (*box).rend);
	else if (box->all_map[(int)(y + dist_y)][(int)(x + dist_x + 0.15)] != 34
		&& box->all_map[(int)(y + dist_y)][(int)(x + dist_x + 0.15)] != 9)
		box->bag.Message = NULL;
	if (box->keys[SDL_SCANCODE_E] == 1 &&
		box->all_map[(int)(y + dist_y)][(int)(x + dist_x + 0.15)] == 9)
		end_level(box);
}

void		door_open_message(t_box *box, double x, double y)
{
	double	dist_x;
	double	dist_y;

	dist_x = fabs(box->cam.d.x) > fabs(box->cam.d.y) ? box->cam.d.x : 0;
	dist_y = fabs(box->cam.d.x) <= fabs(box->cam.d.y) ? box->cam.d.y : 0;
	if (box->all_map[(int)(y + dist_y)][(int)(x + dist_x + 0.15)] == 34 &&
		box->bag.Message == NULL)
		box->bag.Message = renderText_blue("Press 'E' to open the doors", 
			"ttf/mainfont.ttf", 22, (*box).rend);
	else if (box->all_map[(int)(y + dist_y)][(int)(x + dist_x + 0.15)] != 34
		&& box->all_map[(int)(y + dist_y)][(int)(x + dist_x + 0.15)] != 9)
		box->bag.Message = NULL;
	graal_message(box, x, y);
}

void		check_doors(t_box *box, double x, double y)
{
	double	dist_x;
	double	dist_y;

	health_pickup(box, x, y, 0.05);
	dist_x = fabs(box->cam.d.x) > fabs(box->cam.d.y) ? box->cam.d.x : 0;
	dist_y = fabs(box->cam.d.x) <= fabs(box->cam.d.y) ? box->cam.d.y : 0;
	if (box->keys[SDL_SCANCODE_E] == 1 && box->bag.n_items > 0 &&
		box->all_map[(int)(y + dist_y)][(int)(x + dist_x + 0.15)] == 34)
	{
		box->all_map[(int)(y + dist_y)][(int)(x + dist_x + 0.15)] = 1;
		lost_key(box);
	}
	else if (box->keys[SDL_SCANCODE_E] == 1 && box->bag.n_items <= 0 &&
		box->all_map[(int)(y + dist_y)][(int)(x + dist_x + 0.15)] == 34)
	{
		box->bag.Message = NULL;
		box->bag.Message = renderText_red("You don't have keys!", 
			"ttf/mainfont.ttf", 30, (*box).rend);
		box->bag.time = 1;
	}
	if (box->bag.time == 75)
		box->bag.Message = NULL;
	box->bag.time = (box->bag.time > 90) ? 0 : (box->bag.time + 1);
}

int			paint_this(t_box *box)
{
	double 	cam_pos_x;
	double	cam_pos_y;

	SDL_RenderClear(box->rend);
	cam_pos_y = box->cam.position.y;
	cam_pos_x = box->cam.position.x;
	door_open_message(box, cam_pos_x, cam_pos_y);
	check_doors(box, cam_pos_x, cam_pos_y);
	some_pthreads(box);
	take_sprite(box, cam_pos_x, cam_pos_y);
	just_travel_s(box, cam_pos_x, cam_pos_y);
	some_rotation(box);
	SDL_UpdateTexture(box->main_t, NULL, box->pixels, WIND_W * sizeof(Uint32));
	SDL_RenderCopy(box->rend, box->main_t, NULL, NULL );
	paint_hud(box);
	SDL_RenderPresent(box->rend);
	return (0);
}


void		just_travel_w(t_box *box, double x, double y, double a)
{
	double		d_x;
	double		d_y;

	d_x = box->cam.d.x;
	d_y = box->cam.d.y;
	if (box->keys[SDL_SCANCODE_W] == 1)
	{
		ft_check_walk(box);
		if ((box->all_map[(int)(y + a)][(int)(x + d_x * box->go.spd - a)]) < 3 &&
			(box->all_map[(int)(y + a)][(int)(x + d_x * box->go.spd + a)]) < 3 &&
			(box->all_map[(int)(y - a)][(int)(x + d_x * box->go.spd - a)]) < 3 &&
			(box->all_map[(int)(y - a)][(int)(x + d_x * box->go.spd + a)]) < 3)
			box->cam.position.x += box->cam.d.x * box->go.spd;
		if ((box->all_map[(int)(y + d_y * box->go.spd + a)][(int)(x + a)]) < 3 &&
			(box->all_map[(int)(y + d_y * box->go.spd + a)][(int)(x - a)]) < 3 &&
			(box->all_map[(int)(y + d_y * box->go.spd - a)][(int)(x + a)]) < 3 &&
			(box->all_map[(int)(y + d_y * box->go.spd - a)][(int)(x - a)]) < 3)
			box->cam.position.y += box->cam.d.y * box->go.spd;
	}
}

void		just_travel_s(t_box *box, double x, double y)
{
	double a;
	double d_x;
	double d_y;

	d_x = box->cam.d.x;
	d_y = box->cam.d.y;
	a = 0.15;
	if (box->keys[SDL_SCANCODE_S] == 1)
	{
		ft_check_walk(box);
		if ((box->all_map[(int)(y + a)][(int)(x - d_x * box->go.spd - a)]) < 3 &&
			(box->all_map[(int)(y + a)][(int)(x - d_x * box->go.spd + a)]) < 3 &&
			(box->all_map[(int)(y - a)][(int)(x - d_x * box->go.spd - a)]) < 3 &&
			(box->all_map[(int)(y - a)][(int)(x - d_x * box->go.spd + a)]) < 3)
			box->cam.position.x -= box->cam.d.x * box->go.spd;
		if ((box->all_map[(int)(y - d_y * box->go.spd + a)][(int)(x + a)]) < 3 &&
			(box->all_map[(int)(y - d_y * box->go.spd + a)][(int)(x - a)]) < 3 &&
			(box->all_map[(int)(y - d_y * box->go.spd - a)][(int)(x - a)]) < 3 &&
			(box->all_map[(int)(y - d_y * box->go.spd - a)][(int)(x + a)]) < 3)
			box->cam.position.y -= box->cam.d.y * box->go.spd;
	}
	just_travel_w(box, x, y, a);
	go_left(box, x, y, a);
	if (box->fly_mode == 0)
		ttsky_and_sit(box);
}

void		go_right(t_box *box, double x, double y, double a)
{
	double	p_x;
	double	p_y;

	p_x = box->cam.p.x;
	p_y = box->cam.p.y;
	if (box->keys[SDL_SCANCODE_D] == 1)
	{
		ft_check_walk(box);
		if ((box->all_map[(int)(y + a)][(int)(x + p_x * box->go.spd + a)]) < 3 &&
			(box->all_map[(int)(y - a)][(int)(x + p_x * box->go.spd + a)]) < 3 &&
			(box->all_map[(int)(y + a)][(int)(x + p_x * box->go.spd - a)]) < 3 &&
			(box->all_map[(int)(y - a)][(int)(x + p_x * box->go.spd - a)]) < 3)
			box->cam.position.x += box->cam.p.x * box->go.spd;
		if ((box->all_map[(int)(y + p_y * box->go.spd - a)][(int)(x + a)]) < 3 &&
			(box->all_map[(int)(y + p_y * box->go.spd + a)][(int)(x + a)]) < 3 &&
			(box->all_map[(int)(y + p_y * box->go.spd - a)][(int)(x - a)]) < 3 &&
			(box->all_map[(int)(y + p_y * box->go.spd + a)][(int)(x - a)]) < 3)
			box->cam.position.y += box->cam.p.y * box->go.spd;
		}
}

void		go_left(t_box *box, double x, double y, double a)
{
	double	p_x;
	double	p_y;

	p_x = box->cam.p.x;
	p_y = box->cam.p.y;
	if (box->keys[SDL_SCANCODE_A] == 1)
	{
		ft_check_walk(box);
		if ((box->all_map[(int)(y + a)][(int)(x - p_x * box->go.spd + a)]) < 3 &&
			(box->all_map[(int)(y + a)][(int)(x - p_x * box->go.spd - a)]) < 3 &&
			(box->all_map[(int)(y - a)][(int)(x - p_x * box->go.spd + a)]) < 3 &&
			(box->all_map[(int)(y - a)][(int)(x - p_x * box->go.spd - a)]) < 3)
			box->cam.position.x -= box->cam.p.x * box->go.spd;
		if ((box->all_map[(int)(y - p_y * box->go.spd - a)][(int)(x - a)]) < 3 &&
			(box->all_map[(int)(y - p_y * box->go.spd + a)][(int)(x - a)]) < 3 &&
			(box->all_map[(int)(y - p_y * box->go.spd - a)][(int)(x + a)]) < 3 &&
			(box->all_map[(int)(y - p_y * box->go.spd + a)][(int)(x + a)]) < 3)
			box->cam.position.y -= box->cam.p.y * box->go.spd;
	}
	go_right(box, x, y, a);
}

void		some_rotation(t_box *box)
{
	double	i;

	box->ogo.rot_spd = 0.025;
	if (box->keys[SDL_SCANCODE_SEMICOLON] == 1 || box->keys[SDL_SCANCODE_K] == 1)
	{
		if (box->keys[SDL_SCANCODE_K] == 1)
			box->ogo.rot_spd = -box->ogo.rot_spd;
		i = box->cam.d.x;
		box->cam.d.x = box->cam.d.x * cos(box->ogo.rot_spd) -
			box->cam.d.y * sin(box->ogo.rot_spd);
		box->cam.d.y = i * sin(box->ogo.rot_spd) +
			box->cam.d.y * cos(box->ogo.rot_spd);
		i = box->cam.p.x;
		box->cam.p.x = box->cam.p.x * cos(box->ogo.rot_spd) -
			box->cam.p.y * sin(box->ogo.rot_spd);
		box->cam.p.y = i * sin(box->ogo.rot_spd) +
			box->cam.p.y * cos(box->ogo.rot_spd);
	}
	if (box->keys[SDL_SCANCODE_O] == 1 && box->ogo.lop < WIND_H / 2)
		box->ogo.lop += 20;
	if (box->keys[SDL_SCANCODE_L] == 1 && box->ogo.lop > -WIND_H / 2)
		box->ogo.lop -= 20;
}

void	ttsky_and_sit(t_box *box)
{
	if (box->ttsky2 == 1 && box->go.lop < 0.55)
		box->go.lop += 0.04;
	if (box->go.lop >= 0.55)
		box->ttsky2 = 0;
	if (box->ttsky2 == 0 && box->go.lop > 0)
		box->go.lop -= 0.04;
	if (box->sitd == 1 && box->go.lop > -0.5)
		box->go.lop -= 0.1;
	if (box->sitd == 0 && box->go.lop < 0)
	{
		box->go.lop += 0.1;
		box->go.lop = box->go.lop > 0 ? 0 : box->go.lop;
	}
}
