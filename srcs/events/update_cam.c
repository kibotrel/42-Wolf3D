/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 18:25:56 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/25 19:55:45 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "env.h"
#include "wolf3d.h"

void	change_angle(char *key, double *angle, t_pos mouse, t_env *env)
{
	if (key[SDL_SCANCODE_COMMA] || mouse.x < env->w / 2)
		*angle = (*angle >= 358 ? 362 - *angle : *angle + 2);
	else if (key[SDL_SCANCODE_PERIOD] || mouse.x > env->w / 2)
		*angle = (*angle <= 2 ? 358 + *angle : *angle - 2);
}

void	change_height(char *key, t_env *env, t_pos mouse, t_pos *flags)
{
	if (key[SDL_SCANCODE_PAGEUP] || mouse.y < env->h / 2)
		env->cam.offset += 15;
	else if (key[SDL_SCANCODE_PAGEDOWN] || mouse.y > env->h / 2)
		env->cam.offset -= 15;
	if (env->cam.offset > env->h / 2)
		env->cam.offset = env->h / 2;
	else if (env->cam.offset < -(env->h / 2))
		env->cam.offset = -(env->h / 2);
	flags->y = 1;
}
