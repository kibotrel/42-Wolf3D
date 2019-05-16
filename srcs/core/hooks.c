/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 18:02:39 by kibotrel          #+#    #+#             */
/*   Updated: 2019/05/16 10:40:57 by nde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "env.h"
#include "wolf3d.h"


static void		keypress(t_env *env, SDL_Keysym key)
{
	if (key.sym == SDLK_COMMA || key.sym == SDLK_PERIOD)
		change_angle(env, key.sym, &env->cam.angle);
	if (key.sym == SDLK_w || key.sym == SDLK_s || key.sym == SDLK_a
		|| key.sym == SDLK_d)
		move(env, key.sym);
	else if (key.sym == SDLK_PAGEUP || key.sym == SDLK_PAGEDOWN)
		change_height(env, key.sym, &env->cam.height);
	else if (key.sym == SDLK_SPACE)
		place_block(env);
	else if (key.sym == SDLK_r)
	{
		cam_setup(&env->cam);
		raycast(env->map, env, &env->cam, &env->ray);
	}
}

void			hooks(t_env *env, int *loop)
{
	SDL_PollEvent(&env->sdl.event);
	if (env->sdl.event.window.event == SDL_WINDOWEVENT_CLOSE
		|| env->sdl.event.key.keysym.sym == SDLK_ESCAPE)
		*loop = 0;
	else if (env->sdl.event.type == SDL_KEYDOWN)
		keypress(env, env->sdl.event.key.keysym);
}
