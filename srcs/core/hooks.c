/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 18:02:39 by kibotrel          #+#    #+#             */
/*   Updated: 2019/05/13 20:19:59 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "env.h"
#include "wolf3d.h"

static void	keypress(t_env *env, SDL_Keysym key)
{
	if (key.sym == SDLK_COMMA || key.sym == SDLK_PERIOD)
		change_angle(env, env->sdl.event.key.keysym);
	else if (key.sym = SDL_w)
		move_forward(env);

}

void	hooks(t_env *env, int *loop)
{
	SDL_PollEvent(&env->sdl.event);
	if (env->sdl.event.window.event == SDL_WINDOWEVENT_CLOSE
		|| env->sdl.event.key.keysym.sym == SDLK_ESCAPE)
		event = 0;
	else if (env->sdl.event.type == SDL_KEYDOWN)
		keypress(env, env->sdl.event.key.keysym);
	else if (env->sdl.event.key.keysym.sym == SDLK_w)
	{
		neg = ((env->cam.angle < R_N && env->cam.angle > R_E) || (env->cam.angle > R_W && env->cam.angle < R_S)) ? -1 : 1;
		env->cam.coord.x += cos(env->cam.angle) * 16 * neg;
		env->cam.coord.y -= sin(env->cam.angle) * 16;
		raycast(env->map, &env->sdl, &env->cam , &env->ray);
	}
	else if (env->sdl.event.key.keysym.sym == SDLK_s)
	{
		neg = ((env->cam.angle < R_N && env->cam.angle > R_E) || (env->cam.angle > R_W && env->cam.angle < R_S)) ? -1 : 1;
		env->cam.coord.x -= cos(env->cam.angle) * 16 * neg;
		env->cam.coord.y += sin(env->cam.angle) * 16;
		raycast(env->map, &env->sdl, &env->cam , &env->ray);
	}
	else if (env->sdl.event.key.keysym.sym == SDLK_a)
	{
		neg = ((env->cam.angle + R_N < R_N && env->cam.angle + R_N > R_E) || (env->cam.angle + R_N > R_W && env->cam.angle + R_N < R_S)) ? -1 : 1;
		env->cam.coord.x += cos(env->cam.angle + R_N) * 10;
		env->cam.coord.y -= sin(env->cam.angle + R_N) * 10;
		raycast(env->map, &env->sdl, &env->cam , &env->ray);
	}
	else if (env->sdl.event.key.keysym.sym == SDLK_d)
	{
		neg = ((env->cam.angle + R_N < R_N && env->cam.angle + R_N > R_E) || (env->cam.angle + R_N > R_W && env->cam.angle + R_N < R_S)) ? -1 : 1;
		env->cam.coord.x -= cos(env->cam.angle + R_N) * 10;
		env->cam.coord.y += sin(env->cam.angle + R_N) * 10;
		raycast(env->map, &env->sdl, &env->cam , &env->ray);
	}
}
