/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 18:02:39 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/10 17:06:01 by reda-con         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "env.h"
#include "wolf3d.h"
#include "libft.h"

static void	change_cam(t_env *env, t_mouse *mouse, char *key, t_pos *fl)
{
	mouse->old.x = mouse->new.x;
	mouse->old.y = mouse->new.y;
	mouse->new.x = env->sdl.event.motion.x;
	mouse->new.y = env->sdl.event.motion.y;
	if (mouse->new.x != mouse->old.x)
		change_angle(key, &env->cam.angle, mouse->new, env);
	if (mouse->new.y != mouse->old.y)
		change_height(key, env, mouse->new, fl);
	fl->y = 1;
	SDL_WarpMouseInWindow(env->sdl.win, env->w / 2, env->h / 2);
}

void		trigger_event(char *key, t_env *env, t_mouse *mouse, t_pos *fl)
{
	while (SDL_PollEvent(&env->sdl.event))
	{
		if (env->sdl.event.type == SDL_KEYDOWN)
			key[env->sdl.event.key.keysym.scancode] = 1;
		if (env->sdl.event.type == SDL_KEYUP)
			key[env->sdl.event.key.keysym.scancode] = 0;
		if (env->sdl.event.type == SDL_MOUSEMOTION && mouse->toggle_mouse == 1)
			change_cam(env, mouse, key, fl);
		//		if (env->sdl.event.window.event == SDL_WINDOWEVENT_RESIZED)
		//			resize(env, &env->sdl);
		if (env->sdl.event.window.event == SDL_WINDOWEVENT_CLOSE)
			fl->x = 0;
	}
}

static void	next_process(char *key, t_env *env, t_pos *fl, t_mouse *mouse)
{
	if (key[SDL_SCANCODE_R])
	{
		cam_setup(&env->cam);
		fl->y = 1;
	}
	mouse->curr_time = SDL_GetTicks();
	if (key[SDL_SCANCODE_SPACE] && mouse->curr_time > mouse->old_time + 100)
	{
		mouse->old_time = mouse->curr_time;
		place_block(env, fl);
	}
	if (key[SDL_SCANCODE_LSHIFT])
		env->cam.sprint = 2;
	else
		env->cam.sprint = 1;
	if (key[SDL_SCANCODE_W] || key[SDL_SCANCODE_S]\
		|| key[SDL_SCANCODE_A] || key[SDL_SCANCODE_D])
		move(env, key, fl);
	if (key[SDL_SCANCODE_LCTRL])
	{
		env->cam.crouch = 500;
		fl->y = 1;
	}
	else
	{
		env->cam.crouch = 0;
		fl->y = 1;
	}
}

static void	process_event(char *key, t_env *env, t_mouse *mouse, t_pos *fl)
{
	int		i;

	i = 0;
	mouse->curr_time = SDL_GetTicks();
	if (mouse->toggle_mouse == 1)
	{
		if (key[SDL_SCANCODE_COMMA] || key[SDL_SCANCODE_PERIOD])
		{
			change_angle(key, &env->cam.angle, mouse->new, env);
			fl->y = 1;
		}
		if (key[SDL_SCANCODE_PAGEUP] || key[SDL_SCANCODE_PAGEDOWN])
			change_height(key, env, mouse->new, fl);
		if (key[SDL_SCANCODE_TAB] && env->height <= 20 && env->width <= 25)
		{
			fl->y = 1;
			i = 1;
		}
		next_process(key, env, fl, mouse);
	}
	if (fl->y == 1)
		upload_image(env, i);
}

void		hooks(t_env *env, t_pos *flags, char *key, t_mouse *mouse)
{
	trigger_event(key, env, mouse, flags);
	if (key[SDL_SCANCODE_ESCAPE])
		flags->x = 0;
	if (key[SDL_SCANCODE_P] && mouse->curr_time > mouse->old_time + 100)
	{
		enable_mouse(&env->mouse);
		flags->y = 1;
	}
	process_event(key, env, mouse, flags);
}
