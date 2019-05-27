/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 18:02:39 by kibotrel          #+#    #+#             */
/*   Updated: 2019/05/27 19:09:02 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "env.h"
#include "wolf3d.h"
#include "libft.h"

#include <stdio.h>
/*
static void		keypress(t_env *env, SDL_Keysym key)
{
	if (key.sym == SDLK_COMMA || key.sym == SDLK_PERIOD)
		change_angle(env, key.sym, &env->cam.angle);
	if (key.sym == SDLK_w || key.sym == SDLK_s || key.sym == SDLK_a
		|| key.sym == SDLK_d)
		move(env, key.sym);
	if (key.sym == SDLK_PAGEUP || key.sym == SDLK_PAGEDOWN)
		change_height(env, key.sym, &env->cam.height, 1);
	if (key.sym == SDLK_SPACE)
		place_block(env);
}
*/

void			change_cam(t_env *env, char *key, t_pos *mickey)
{
	mickey->x = env->sdl.event.motion.x;
	mickey->y = env->sdl.event.motion.y;
	change_angle(env, key, &env->cam.angle, *mickey);
	change_height(env, key, &env->cam.offset, 5, *mickey);
	SDL_WarpMouseInWindow(env->sdl.win, WIDTH / 2, HEIGHT / 2);
}

void			all_ev(char *key, SDL_Event *ev, t_env *env, t_pos *mouse)
{
	while (SDL_PollEvent(ev))
	{
		if (ev->type == SDL_KEYDOWN)
			key[ev->key.keysym.scancode] = 1;
		if (ev->type == SDL_KEYUP)
			key[ev->key.keysym.scancode] = 0;
		if (ev->type == SDL_MOUSEMOTION)
			change_cam(env, key, mouse);
	}
}

void			hooks(t_env *env, int *loop, char *key)
{
	t_pos	mouse;

	mouse.x = WIDTH / 2;
	mouse.y = HEIGHT / 2;
	all_ev(key, &env->sdl.event, env, &mouse);
	if (key[SDL_SCANCODE_ESCAPE]
		|| env->sdl.event.window.event == SDL_WINDOWEVENT_CLOSE)
		*loop = 0;
	if (key[SDL_SCANCODE_COMMA] || key[SDL_SCANCODE_PERIOD])
		change_angle(env, key, &env->cam.angle, mouse);
	if (key[SDL_SCANCODE_W] || key[SDL_SCANCODE_S]
		|| key[SDL_SCANCODE_A] || key[SDL_SCANCODE_D])
		move(env, key);
	if (key[SDL_SCANCODE_PAGEUP] || key[SDL_SCANCODE_PAGEDOWN])
		change_height(env, key, &env->cam.offset, 1, mouse);
	if (key[SDL_SCANCODE_R])
	{
		cam_setup(&env->cam);
		raycast(env);
	}
	if (key[SDL_SCANCODE_SPACE])
		place_block(env);
}
