/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 22:53:09 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/18 11:53:52 by nde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "SDL.h"
#include "libft.h"
#include "env.h"
#include "wolf3d.h"

void	sdl_setup(t_sdl *sdl, t_env *env)
{
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		free_switch(env, 1);
		ft_print_error(ERR_INIT, 12);
	}
	if (!(sdl->win = SDL_CreateWindow("Wolf3D", 0, 0, WIDTH, HEIGHT, RESIZE)))
		free_sdl(env, 1, ERR_WIN, 13);
	if (!(sdl->ren = SDL_CreateRenderer(sdl->win, -1, TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC)))
		free_sdl(env, 2, ERR_RENDERER, 14);
	if (!(sdl->text = SDL_CreateTexture(sdl->ren, ARGB, STREAM, WIDTH, HEIGHT)))
		free_sdl(env, 3, ERR_TEXTURE, 15);
	if (!(sdl->pixels = (uint32_t*)malloc(4 * ((WIDTH + 1) * HEIGHT))))
		free_sdl(env, 4, ERR_MALLOC, 5);
	if (SDL_ShowCursor(SDL_DISABLE) < 0)
		free_sdl(env, 5, ERR_CURSOR, 16);
	SDL_WarpMouseInWindow(sdl->win, WIDTH / 2, HEIGHT / 2);
	// sdl->surf[0] = SDL_LoadBMP("assets/01.bmp");
	// sdl->surf[1] = SDL_LoadBMP("assets/05.BMP");
	// sdl->surf[2] = SDL_LoadBMP("assets/13.BMP");
	// sdl->surf[3] = SDL_LoadBMP("assets/23.BMP");
	// sdl->surf[4] = SDL_LoadBMP("assets/sky3.bmp");
	sdl->colors[0] = 0xff6950;
	sdl->colors[1] = 0x33c47f;
	sdl->colors[2] = 0xa061d1;
	sdl->colors[3] = 0x1c4f99;
	sdl->colors[4] = 0x00ffff;
	sdl->colors[5] = 0xc8c8c8;
}
