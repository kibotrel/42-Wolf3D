/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 22:53:09 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/27 15:25:06 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "SDL.h"
#include "png.h"
#include "macros.h"
#include "libft.h"
#include "env.h"
#include "wolf3d.h"

static void	load_textures(t_sdl *sdl)
{
	png_to_array("assets/cracked_stone_bricks.png", &sdl->surf[0], 0);
	sdl->colors[0] = WALL_ORDER;
	png_to_array("assets/chiseled_stone_bricks.png", &sdl->surf[1], 0);
	sdl->colors[1] = WALL_ALLIANCE;
	png_to_array("assets/stone_bricks.png", &sdl->surf[2], 0);
	sdl->colors[2] = WALL_ASSEMBLY;
	png_to_array("assets/mossy_stone_bricks.png", &sdl->surf[3], 0);
	sdl->colors[3] = WALL_FEDERATION;
}

void	sdl_setup(t_sdl *sdl, t_env *env)
{
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		free_switch(env, 1);
		ft_print_error(E_INIT, 12);
	}
	if (!(sdl->win = SDL_CreateWindow("Wolf3D", 0, 0, WIDTH, HEIGHT, RESIZE)))
		free_sdl(env, 1, E_WIN, 13);
	if (!(sdl->ren = SDL_CreateRenderer(sdl->win, -1, TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC)))
		free_sdl(env, 2, E_RENDERER, 14);
	if (!(sdl->text = SDL_CreateTexture(sdl->ren, ARGB, STREAM, WIDTH, HEIGHT)))
		free_sdl(env, 3, E_TEXTURE, 15);
	if (!(sdl->pixels = (uint32_t*)malloc(4 * ((WIDTH + 1) * HEIGHT))))
		free_sdl(env, 4, E_MALLOC, 5);
	if (SDL_ShowCursor(SDL_DISABLE) < 0)
		free_sdl(env, 5, E_CURSOR, 16);
	sdl->set_fs = 0;
	SDL_WarpMouseInWindow(sdl->win, WIDTH / 2, HEIGHT / 2);
	load_textures(sdl);
}
