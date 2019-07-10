/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 13:44:19 by kibotrel          #+#    #+#             */
/*   Updated: 2019/07/10 14:02:59 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "env.h"
#include "wolf3d.h"

void	trigger_event(char *key, t_env *env, t_mouse *mouse, t_pos *fl)
{
	while (SDL_PollEvent(&env->sdl.event))
	{
		if (env->sdl.event.window.event == SDL_WINDOWEVENT_RESIZED)
			resize(env, &env->sdl, 1);
		if (env->sdl.event.type == SDL_KEYDOWN)
			key[env->sdl.event.key.keysym.scancode] = 1;
		if (env->sdl.event.type == SDL_KEYUP)
			key[env->sdl.event.key.keysym.scancode] = 0;
		if (env->sdl.event.type == SDL_MOUSEMOTION && mouse->toggle_mouse == 1)
			change_cam(env, mouse, key, fl);
		if (env->sdl.event.window.event == SDL_WINDOWEVENT_CLOSE)
			fl->x = 0;
	}
}

void	next_process(char *key, t_env *env, t_pos *fl, t_mouse *mouse)
{
	if (key[SDL_SCANCODE_R])
	{
		cam_setup(&env->cam);
		fl->y = 1;
	}
	if (key[SDL_SCANCODE_LSHIFT])
		env->cam.sprint = 3;
	else
		env->cam.sprint = 1;
	if (key[SDL_SCANCODE_W] || key[SDL_SCANCODE_S]
		|| key[SDL_SCANCODE_A] || key[SDL_SCANCODE_D])
		move(env, key, fl);
	if (key[SDL_SCANCODE_T] && mouse->curr_time > mouse->old_time + 500)
	{
		env->tex_on *= -1;
		mouse->old_time = mouse->curr_time;
	}
	if (key[SDL_SCANCODE_F] && mouse->curr_time > mouse->old_time + 500)
	{
		set_fullscreen(env);
		mouse->old_time = mouse->curr_time;
		fl->y = 1;
	}
}

void	process_event(char *key, t_env *env, t_mouse *mouse, t_pos *fl)
{
	if (mouse->toggle_mouse == 1)
	{
		if (key[SDL_SCANCODE_COMMA] || key[SDL_SCANCODE_PERIOD])
		{
			change_angle(key, &env->cam.angle, mouse->new, env);
			fl->y = 1;
		}
		if (key[SDL_SCANCODE_PAGEUP] || key[SDL_SCANCODE_PAGEDOWN])
			change_height(key, env, mouse->new, fl);
		if (key[SDL_SCANCODE_TAB] && mouse->curr_time > mouse->old_time + 500)
		{
			fl->y = 1;
			mouse->toggle_map *= -1;
			mouse->old_time = mouse->curr_time;
		}
		next_process(key, env, fl, mouse);
	}
	if (fl->y == 1)
		upload_image(env, mouse->toggle_map);
}
