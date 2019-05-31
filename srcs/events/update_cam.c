/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 18:25:56 by kibotrel          #+#    #+#             */
/*   Updated: 2019/05/31 12:06:43 by reda-con         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "env.h"
#include "wolf3d.h"

void	change_angle(char *key, double *angle, t_pos mouse, t_env *env)
{
	if (key[SDL_SCANCODE_COMMA] || mouse.x <  env->w / 2)
	{
		*angle += to_rad(2);
		*angle = (*angle >= to_rad(360)) ? to_rad(360) - *angle : *angle;
	}
	else if (key[SDL_SCANCODE_PERIOD] || mouse.x > env->w / 2)
	{
		*angle -= to_rad(2);
		*angle = (*angle < 0) ? to_rad(360) + *angle : *angle;
	}
}

void	change_height(char *key, t_env *env, int speed, t_pos mouse)
{
	double	*height;

	height = &env->cam.height;
	if (key[SDL_SCANCODE_PAGEUP] || mouse.y < env->h / 2)
		*height += 4 * speed;
	else if (key[SDL_SCANCODE_PAGEDOWN] || mouse.y > env->h / 2)
		*height -= 4 * speed;
	if (*height > HEIGHT_CAM)
		*height = HEIGHT_CAM;
	else if (*height < -HEIGHT_CAM)
		*height = -HEIGHT_CAM;
}
