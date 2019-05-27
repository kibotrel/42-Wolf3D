/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 18:02:39 by kibotrel          #+#    #+#             */
/*   Updated: 2019/05/27 17:08:23 by reda-con         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "env.h"
#include "wolf3d.h"
#include "libft.h"

#include <stdio.h>

void			change_cam(t_env *env, t_mouse *mouse, char *key, int *fl)
{
	mouse->old.x = mouse->new.x;
	mouse->old.y = mouse->new.y;
	mouse->new.x = env->sdl.event.motion.x;
	mouse->new.y = env->sdl.event.motion.y;
	if (mouse->new.x != mouse->old.x)
		change_angle(key, &env->cam.angle, mouse->new);
	if (mouse->new.y != mouse->old.y)
		change_height(key, &env->cam.height, 5, mouse->new);
	*fl = 1;
	SDL_WarpMouseInWindow(env->sdl.win, WIDTH / 2, HEIGHT / 2);
//	printf("%f; %f; %f; %f\n", old->x, old->y, new->x, new->y);
}

void			all_ev(char *key, t_env *env, t_mouse *mouse, int *fl)
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

void			hooks(t_env *env, int *loop, char *key, t_mouse *mouse)
{
	int		fl;

	fl = 0;
	all_ev(key, env, mouse, &fl);
	if (key[SDL_SCANCODE_ESCAPE]\
		|| env->sdl.event.window.event == SDL_WINDOWEVENT_CLOSE)
		*loop = 0;
	if (key[SDL_SCANCODE_COMMA] || key[SDL_SCANCODE_PERIOD])
	{
		change_angle(key, &env->cam.angle, mouse->new);
		fl = 1;
	}
	if (key[SDL_SCANCODE_W] || key[SDL_SCANCODE_S]\
		|| key[SDL_SCANCODE_A] || key[SDL_SCANCODE_D])
	{
		move(env, key, 0);
		fl = 1;
	}
	if (key[SDL_SCANCODE_PAGEUP] || key[SDL_SCANCODE_PAGEDOWN])
	{
		change_height(key, &env->cam.height, 1, mouse->new);
		fl = 1;
	}
	if (key[SDL_SCANCODE_R])
	{
		cam_setup(&env->cam);
		raycast(env->map, env, &env->cam, &env->ray);
		fl = 1;
	}
	if (key[SDL_SCANCODE_SPACE])
	{
		place_block(env);
		fl = 1;
	}
	if (fl == 1)
		raycast(env->map, env, &env->cam, &env->ray);
}
