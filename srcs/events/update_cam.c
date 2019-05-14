/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 18:25:56 by kibotrel          #+#    #+#             */
/*   Updated: 2019/05/14 15:50:14 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "env.h"
#include "wolf3d.h"

void	change_angle(t_env *env, double *angle, SDL_Keysym key)
{
	if (key.sym == SDLK_COMMA)
	{
		*angle += to_rad(2);
		*angle = (*angle > to_rad(360) ? to_rad(360) - *angle : *angle);
	}
	else
	{
		*angle -= to_rad(2);
		*angle = (angle < 0 ? to_rad(360) + *angle : *angle);
	}
	raycast(env->map, env, &env->cam, &env->ray);
}
