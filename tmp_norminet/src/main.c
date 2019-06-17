/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 22:10:41 by aperesad          #+#    #+#             */
/*   Updated: 2019/06/17 22:10:43 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		add_resources(t_box *box)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		fatal_error(1, box);
	if ((box->wind = SDL_CreateWindow("Doom Nukem", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIND_W, WIND_H, 0)) == NULL)
		fatal_error(2, box);
	if ((box->rend = SDL_CreateRenderer(box->wind, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) == NULL)
		fatal_error(3, box);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		fatal_error(8, box);
	if (TTF_Init() != 0)
		fatal_error(4, box);
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
		fatal_error(4, box);
}

int			main(void)
{
	t_box	box;

	box.sprites.n_sprites = 0;
	box.bag.posX = 5;
	box.bag.posY = WIND_H - WIND_H / 5 + 5;
	box.bag.n_items = 0;
	add_resources(&box);
	start_game(&box);
	return (0);
}
