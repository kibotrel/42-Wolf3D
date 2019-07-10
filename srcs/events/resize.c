/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 09:23:03 by nde-jesu          #+#    #+#             */
/*   Updated: 2019/07/10 15:38:09 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "wolf3d.h"
#include "env.h"

void	resize(t_env *env, t_sdl *sdl, int flag)
{
	if (flag == 1)
	{
		env->w = env->sdl.event.window.data1;
		env->h = env->sdl.event.window.data2;
		if (env->w < 500 || env->h < 500)
		{
			SDL_SetWindowSize(sdl->win, 500, 500);
			env->w = 500;
			env->h = 500;
		}
	}
	free(sdl->pixels);
	SDL_DestroyTexture(sdl->text);
	sdl->text = SDL_CreateTexture(sdl->ren, ARGB, STREAM, env->w, env->h);
	if (!(sdl->pixels = (uint32_t*)malloc(4 * ((env->w + 1) * env->h))))
		return ;
	SDL_WarpMouseInWindow(env->sdl.win, env->w / 2, env->h / 2);
	raycast(env, &env->ray);
}
