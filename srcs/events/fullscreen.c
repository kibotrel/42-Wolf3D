/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fullscreen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 15:31:29 by kibotrel          #+#    #+#             */
/*   Updated: 2019/07/10 15:35:13 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "wolf3d.h"

void	set_fullscreen(t_env *env)
{
	if (env->sdl.set_fs != 0)
		env->sdl.set_fs = 0;
	else
		env->sdl.set_fs = SDL_WINDOW_FULLSCREEN_DESKTOP;
	SDL_SetWindowFullscreen(env->sdl.win, env->sdl.set_fs);
	SDL_GetWindowSize(env->sdl.win, &env->w, &env->h);
	resize(env, &env->sdl, 0);
}
