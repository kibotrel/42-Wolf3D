/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 18:25:56 by kibotrel          #+#    #+#             */
/*   Updated: 2019/05/16 09:08:39 by nde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "env.h"
#include "wolf3d.h"

void	change_angle(t_env *env, SDL_Keycode key, double *angle)
{
	if (key == SDLK_COMMA)
	{
		*angle += to_rad(2);
		*angle = (*angle >= to_rad(360)) ? to_rad(360) - *angle : *angle;
	}
	else
	{
		*angle -= to_rad(2);
		*angle = (*angle < 0) ? to_rad(360) + *angle : *angle;
	}
	raycast(env->map, env, &env->cam, &env->ray);
}

void	change_height(t_env *env, SDL_Keycode key, double *height)
{
	if (key == SDLK_PAGEUP)
		*height += 2;
	else
		*height -= 2;
	if (*height > HEIGHT_CAM)
		*height = HEIGHT_CAM;
	else if (*height < -HEIGHT_CAM)
		*height = -HEIGHT_CAM;
	raycast(env->map, env, &env->cam, &env->ray);
}