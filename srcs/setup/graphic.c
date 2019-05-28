/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 22:53:09 by kibotrel          #+#    #+#             */
/*   Updated: 2019/05/29 01:32:21 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "env.h"
#include "wolf3d.h"

void	sdl_setup(t_sdl *sdl)
{
	SDL_Init(SDL_INIT_VIDEO);
	//ERROR
	sdl->win = SDL_CreateWindow("Wolf3D", 0, 0, WIDTH, HEIGHT, RESIZE);
	//ERROR
	sdl->render = SDL_CreateRenderer(sdl->win, -1, SDL_RENDERER_TARGETTEXTURE);
	//ERROR
	sdl->texture = SDL_CreateTexture(sdl->render, ARGB, STREAM, WIDTH, HEIGHT);
	//ERROR
	sdl->pixels = (uint32_t*)malloc(sizeof(uint32_t) * ((WIDTH + 1) * HEIGHT));
	//ERROR
	SDL_WarpMouseInWindow(sdl->win, WIDTH / 2, HEIGHT / 2);
	//ERROR
	SDL_ShowCursor(SDL_DISABLE);
	//ERROR
}
