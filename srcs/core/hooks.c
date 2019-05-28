/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 18:02:39 by kibotrel          #+#    #+#             */
/*   Updated: 2019/05/28 07:59:43 by nde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "env.h"
#include "wolf3d.h"
#include "libft.h"

#include <stdio.h>

void			change_cam(t_env *env, t_mouse *mouse, char *key, t_pos *fl)
{
	mouse->old.x = mouse->new.x;
	mouse->old.y = mouse->new.y;
	mouse->new.x = env->sdl.event.motion.x;
	mouse->new.y = env->sdl.event.motion.y;
	if (mouse->new.x != mouse->old.x)
		change_angle(key, &env->cam.angle, mouse->new);
	if (mouse->new.y != mouse->old.y)
		change_height(key, &env->cam.height, 5, mouse->new);
	fl->y = 1;
	SDL_WarpMouseInWindow(env->sdl.win, WIDTH / 2, HEIGHT / 2);
}

void			trigger_event(char *key, t_env *env, t_mouse *mouse, t_pos *fl)
{
	while (SDL_PollEvent(&env->sdl.event))
	{
		if (env->sdl.event.type == SDL_KEYDOWN)
			key[env->sdl.event.key.keysym.scancode] = 1;
		if (env->sdl.event.type == SDL_KEYUP)
			key[env->sdl.event.key.keysym.scancode] = 0;
		if (env->sdl.event.type == SDL_MOUSEMOTION)
			change_cam(env, mouse, key, fl);
	}
}

void			next_process(char *key, t_env *env, t_pos *fl)
{
	if (key[SDL_SCANCODE_R])
	{
		cam_setup(&env->cam);
		raycast(env->map, env, &env->cam, &env->ray);
		fl->y = 1;
	}
	if (key[SDL_SCANCODE_SPACE])
	{
		place_block(env);
		fl->y = 1;
	}
	if (key[SDL_SCANCODE_LSHIFT])
		env->cam.sprint = 2;
	if (key[SDL_SCANCODE_LSHIFT] == 0)
		env->cam.sprint = 1;
}

void			process_event(char *key, t_env *env, t_mouse *mouse, t_pos *fl)
{
	if (key[SDL_SCANCODE_ESCAPE]\
		|| env->sdl.event.window.event == SDL_WINDOWEVENT_CLOSE)
		fl->x = 0;
	if (key[SDL_SCANCODE_COMMA] || key[SDL_SCANCODE_PERIOD])
	{
		change_angle(key, &env->cam.angle, mouse->new);
		fl->y = 1;
	}
	if (key[SDL_SCANCODE_W] || key[SDL_SCANCODE_S]\
		|| key[SDL_SCANCODE_A] || key[SDL_SCANCODE_D])
	{
		move(env, key, 0);
		fl->y = 1;
	}
	if (key[SDL_SCANCODE_PAGEUP] || key[SDL_SCANCODE_PAGEDOWN])
	{
		change_height(key, &env->cam.height, 1, mouse->new);
		fl->y = 1;
	}
	next_process(key, env, fl);
	if (fl->y == 1)
		raycast(env->map, env, &env->cam, &env->ray);
}

void			hooks(t_env *env, t_pos *flags, char *key, t_mouse *mouse)
{
	trigger_event(key, env, mouse, flags);
	process_event(key, env, mouse, flags);
}
