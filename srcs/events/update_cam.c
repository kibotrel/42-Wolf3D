/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 18:25:56 by kibotrel          #+#    #+#             */
/*   Updated: 2019/05/14 15:53:16 by nde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "env.h"
#include "wolf3d.h"

void	change_angle(t_env *env, SDL_Keysym key)
{
	double	*tmp;

	tmp = &env->cam.angle;
	if (key.sym == SDLK_COMMA)
	{
		*tmp += to_rad(2);
		*tmp = (*tmp >= to_rad(360)) ? to_rad(360) - *tmp : *tmp;
	}
	else
	{
		*tmp -= to_rad(2);
		*tmp = (*tmp < 0) ? to_rad(360) + *tmp : *tmp;
	}
	raycast(env->map, env, &env->cam, &env->ray);
}
