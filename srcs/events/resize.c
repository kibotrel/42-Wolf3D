/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 09:23:03 by nde-jesu          #+#    #+#             */
/*   Updated: 2019/05/28 10:22:15 by nde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "wolf3d.h"
#include "env.h"

void	enable_mouse(t_mouse *mouse)
{
		mouse->toggle_mouse *= -1;
		if (mouse->toggle_mouse == 1)
			SDL_ShowCursor(SDL_DISABLE);
		else
			SDL_ShowCursor(SDL_ENABLE);
}


void	resize(t_env *env, t_sdl *sdl)
{
	env->w = env->sdl.event.window.data1;
	env->h = env->sdl.event.window.data2;
	free(sdl->pixels);
	SDL_DestroyTexture(sdl->text);
	sdl->text = SDL_CreateTexture(sdl->ren, ARGB, STREAM, env->w, env->h);
	if (!(sdl->pixels = (uint32_t*)malloc(4 * ((env->w + 1) * env->h))))
		return ;
	raycast(env->map, env, &env->cam, &env->ray);
}