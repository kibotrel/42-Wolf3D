/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 18:02:39 by kibotrel          #+#    #+#             */
/*   Updated: 2019/05/14 16:45:35 by reda-con         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "env.h"
#include "wolf3d.h"

static void		keypress(t_env *env, SDL_Keysym key)
{
	if (key.sym == SDLK_COMMA || key.sym == SDLK_PERIOD)
		change_angle(env, env->sdl.event.key.keysym);
	else if (key.sym == SDLK_w)
		move_forward(env);
	else if (key.sym == SDLK_s)
		move_backward(env);
	else if (key.sym == SDLK_a)
		move_left(env);
	else if (key.sym == SDLK_d)
		move_right(env);
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
