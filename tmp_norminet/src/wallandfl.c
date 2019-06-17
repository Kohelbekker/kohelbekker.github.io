#include "wolf3d.h"

void		some_blocks(t_box *box)
{
	box->block.bd = (box->block.bs == 0) ?
		(box->tir.pl.x - box->cam.position.x + (1 - box->tir.go.x) / 2) / box->tir.fold.x :
		(box->tir.pl.y - box->cam.position.y + (1 - box->tir.go.y) / 2) / box->tir.fold.y;
	box->block.bh = WIND_H / box->block.bd;
	box->block.bt = -box->block.bh / 2;
	box->block.bt -= box->block.bt * box->go.lop;
	box->block.bt += WIND_H / 2 + box->ogo.lop;
	box->block.bb = box->block.bh / 2;
	box->block.bb += box->block.bb * box->go.lop;
	box->block.bb += WIND_H / 2 + box->ogo.lop;
	if (box->block.bt < 0)
		box->block.bt = 0;
	else if (box->block.bt > WIND_H)
		box->block.bt = WIND_H;
	if (box->block.bb > WIND_H)
		box->block.bb = WIND_H;
	else if (box->block.bb < 0)
		box->block.bb = 0;
}

void		add_txtrs(t_box *box, int x, int y)
{
	Uint32		color;
	Uint8		r;
	Uint8		g;
	Uint8		b;
	double		intens;

	if (box->no_shadow == 1 || box->mirror_effect == 1)
		intens = (box->no_shadow == 1) ? 0.68 : 0.8;
	else if (box->block.bd >= 0)
	{
		intens = (box->block.bd < 27) ? (1 / box->block.bd * box->light_power) :
		(0.5 / box->block.bd * box->light_power);
		if (intens > 0.8)
			intens = 0.8;
	}
	if ((x >= 0 && x <= 64) && (y >= 0 && y <= 64))
	{
		SDL_GetRGB(((int *)box->txtrs[box->a]->pixels)[y * 64 + x], box->txtrs[box->a]->format, &r, &g, &b);
		r = r * intens;
		g = g * intens;
		b = b * intens;
		color = SDL_MapRGB(box->txtrs[box->a]->format, r, g, b);
		if (box->atpos < WIND_W && box->btpos < WIND_H && box->atpos >= 0 && box->btpos >= 0)
			box->pixels[box->btpos * WIND_W + box->atpos] = color;
	}
}

void		choose_side_texture(t_box *box)
{
	if (box->a >= 25 && box->a <= 34)
		box->a -= 25;
	if ((box->block.bs == 0 && box->all_map[box->tir.pl.y][box->tir.pl.x + 1] == 1 &&
		box->tir.fold.x < 0 && (box->all_map[box->tir.pl.y][box->tir.pl.x + 2] > 24 &&
		box->all_map[box->tir.pl.y][box->tir.pl.x + 2] < 35)) || (box->block.bs == 1 &&
		box->all_map[box->tir.pl.y + 1][box->tir.pl.x] == 1 && box->tir.fold.y < 0 &&
		(box->all_map[box->tir.pl.y + 2][box->tir.pl.x] < 35 &&
		box->all_map[box->tir.pl.y + 2][box->tir.pl.x] > 24)))
	{
		box->a = 8;
	}
	
}

void		print_walls(t_box *box)
{
	box->a = box->all_map[box->tir.pl.y][box->tir.pl.x];
	choose_side_texture(box);
	box->block.btouch = box->block.bs == 0 ?
		box->cam.position.y + box->block.bd * box->tir.fold.y :
		box->cam.position.x + box->block.bd * box->tir.fold.x;
	box->block.btouch -= (box->block.btouch >= 0) ? (int)box->block.btouch :
		((int)box->block.btouch - 1);
	box->paramtext.x = (int)(box->block.btouch * 64);
	box->paramtext.x = 64 - box->paramtext.x - 1;
	box->btpos = box->block.bt;
	while ((box->btpos <= box->block.bb + 1) && (box->btpos < WIND_H))
	{
		box->paramtext.y = box->btpos - WIND_H / 2 + 
			(box->block.bh / 2) * (-box->go.lop + 1) - box->ogo.lop;
		box->paramtext.y = (box->paramtext.y * 64 / box->block.bh);
		box->paramtext.y %= 64;
		add_txtrs(box, box->paramtext.x, box->paramtext.y);
		box->btpos++;
	}
	box->btpos = box->btpos - 2;
	box->sprites.ZBuffer[box->atpos] = box->block.bd;
	up_and_down(box);
}


void		floor_param(t_box *box)
{
	if (box->block.bs == 0 && box->tir.fold.x > 0)
	{
		box->floor_x = box->tir.pl.x;
		box->floor_y = box->tir.pl.y + box->block.btouch;
	}
	else if (box->block.bs == 0 && box->tir.fold.x < 0)
	{
		box->floor_x = box->tir.pl.x + 1.0;
		box->floor_y = box->tir.pl.y + box->block.btouch;
	}
	else if (box->block.bs == 1 && box->tir.fold.y < 0)
	{
		box->floor_x = box->tir.pl.x + box->block.btouch;
		box->floor_y = box->tir.pl.y + 1.0;
	}
	else
	{
		box->floor_x = box->tir.pl.x + box->block.btouch;
		box->floor_y = box->tir.pl.y;
	}
}

double				intens_calc(t_box *box, int y, int a)
{
	double		intens;
	int			tmp_y;

	if (box->no_shadow == 1)
		intens = 0.67;
	else
	{
		if (a == 5)
			tmp_y = y - WIND_H - box->ogo.lop;
		else
			tmp_y = y - box->ogo.lop;
		intens = (1 - (800.0 / abs(tmp_y)) / 2.0) * 1.4 * box->light_power;
		if (intens > 0.8)
			intens = 0.8;
		if (intens < 0)
			intens = 0;
	}
	return (intens);
}

double				mirror_effect(t_box *box, int a, double intens)
{
	if (a == 5)
	{
		intens = 0.85;
		return(intens);
	}
	else
	{
		if (box->dist > 1.0)
			box->dist = 1.0;
		else
		{
			intens = (1 - box->dist);
			if (intens > 0.85)
				intens = 0.85;
		}
	}
	return(intens);
}

void			add_txtrs2(t_box *box, int y, int a)
{
	Uint32		color;
	double		intens;
	Uint8		r;
	Uint8		g;
	Uint8		b;

	intens = intens_calc(box, y, a);
	if (box->mirror_effect == 1)
		intens = mirror_effect(box, a, intens);
	if (box->atpos < WIND_W && box->btpos < WIND_H)
	{
		if ((box->tex_floor_y >= 0 && box->tex_floor_y <= 64) && (box->tex_floor_x >= 0 && box->tex_floor_x <= 64))
		{
			color = ((int *)box->txtrs[a]->pixels)[box->tex_floor_y * 64 + box->tex_floor_x];
			SDL_GetRGB(color, box->txtrs[a]->format, &r, &g, &b);
			r *= intens;
			g *= intens;
			b *= intens;
			color = SDL_MapRGB(box->txtrs[a]->format, r, g, b);
			box->pixels[y * WIND_W + box->atpos] = color;
		}
	}
}

void		dome_image(double angle, t_box *box)
{
	angle += M_PI;
	angle +=  M_PI * box->atpos / 3 / WIND_H;
	angle -=  M_PI / 6;
	if (angle < 0)
		angle += 2 * M_PI;
	if (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	box->tex_floor_x = angle * box->txtrs[10]->w / (2 * M_PI);
}

void		sky_dome(t_box *box)
{
	double	angle;
	int		i;
	Uint32	color;

	i = 0;
	angle = asin(box->cam.d.x);
	if (isnan(angle))
		angle = M_PI;
	if (!(box->cam.d.y < 0))
		angle *= -1;
	dome_image(angle, box);
	while (i < box->block.bt)
	{
		box->tex_floor_y = (WIND_H / 2 + i - box->ogo.lop) * box->txtrs[10]->h / WIND_H;
		color = ((int *)box->txtrs[10]->pixels)[box->tex_floor_y * box->txtrs[10]->w + box->tex_floor_x];
		box->pixels[i * WIND_W + box->atpos] = color;
		i++;
	}
}

void		up_and_down(t_box *box)
{
	int			j;
	double		tmp_floor_y;
	double		tmp_floor_x;

	floor_param(box);
	j = 0;
	if (box->sky == 0)
	{
		while (j < box->block.bt) //bt - верхня межа стіни
		{
			box->tmp_dist = WIND_H / (2.0 * j - WIND_H - 2 * box->ogo.lop);
			box->dist = (box->tmp_dist / box->block.bd * (box->go.lop - 1));
			tmp_floor_x = box->dist * box->floor_x +
			(1.0 - box->dist) * box->cam.position.x;
			tmp_floor_y = box->dist * box->floor_y +
			(1.0 - box->dist) * box->cam.position.y;
			box->tex_floor_x = (int)(tmp_floor_x * 64) % 64;
			box->tex_floor_y = (int)(tmp_floor_y * 64) % 64;
			add_txtrs2(box, j, 12);
			j++;
		}
	}
	else
		sky_dome(box);
	j = box->block.bb - 1;  /// -1 щоб закрити дірку в 1 рядок під стіною!!!
	while (j < WIND_H)
	{
		box->tmp_dist = WIND_H / (2.0 * j - WIND_H - 2 * box->ogo.lop);
		box->dist = (box->tmp_dist / box->block.bd * (box->go.lop + 1));
		tmp_floor_x = box->dist * box->floor_x +
		(1.0 - box->dist) * box->cam.position.x;
		tmp_floor_y = box->dist * box->floor_y +
		(1.0 - box->dist) * box->cam.position.y;
		box->tex_floor_x = (int)(tmp_floor_x * 64) % 64;
		box->tex_floor_y = abs((int)(tmp_floor_y * 64) % 64);
		add_txtrs2(box, j, 11);
		j++;
	}
}
