/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 22:53:09 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/14 11:35:20 by nde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "SDL.h"
#include "SDL_ttf.h"
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
	TTF_Init();
	if (!(sdl->win = SDL_CreateWindow("Wolf3D", 0, 0, WIDTH, HEIGHT, RESIZE)))
		free_sdl(env, 1, ERR_WIN, 13);
	if (!(sdl->ren = SDL_CreateRenderer(sdl->win, -1, TARGETTEXTURE)))
		free_sdl(env, 2, ERR_RENDERER, 14);
	if (!(sdl->text = SDL_CreateTexture(sdl->ren, ARGB, STREAM, WIDTH, HEIGHT)))
		free_sdl(env, 3, ERR_TEXTURE, 15);
	if (!(sdl->pixels = (uint32_t*)malloc(4 * ((WIDTH + 1) * HEIGHT))))
		free_sdl(env, 4, ERR_MALLOC, 5);
	if (SDL_ShowCursor(SDL_DISABLE) < 0)
		free_sdl(env, 5, ERR_CURSOR, 16);
	SDL_WarpMouseInWindow(sdl->win, WIDTH / 2, HEIGHT / 2);
	sdl->surf[0] = SDL_LoadBMP("01.bmp");
	sdl->surf[1] = SDL_LoadBMP("05.bmp");
	sdl->surf[2] = SDL_LoadBMP("13.bmp");
	sdl->surf[3] = SDL_LoadBMP("23.bmp");
}
