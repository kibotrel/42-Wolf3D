/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 18:25:56 by kibotrel          #+#    #+#             */
/*   Updated: 2019/05/31 14:32:20 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "env.h"
#include "wolf3d.h"

void	change_angle(char *key, double *angle, t_pos mouse, t_env *env)
{
	if (key[SDL_SCANCODE_COMMA] || mouse.x < env->w / 2)
		*angle = (*angle >= 357 ? 363 - *angle : *angle + 3);
	else if (key[SDL_SCANCODE_PERIOD] || mouse.x > env->w / 2)
		*angle = (*angle < 3 ? 357 + *angle : *angle - 3);
}

void	change_height(char *key, t_env *env, int speed, t_pos mouse)
{
	double	*height;

	height = &env->cam.offset;
	if (key[SDL_SCANCODE_PAGEUP] || mouse.y < env->h / 2)
		*height += 4 * speed;
	else if (key[SDL_SCANCODE_PAGEDOWN] || mouse.y > env->h / 2)
		*height -= 2 * speed;
	if (*height > HEIGHT / 2 * 1.75)
		*height = HEIGHT / 2 * 1.75;
	else if (*height < HEIGHT / 8)
		*height = HEIGHT / 8;
}
