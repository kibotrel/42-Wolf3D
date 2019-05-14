/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 18:25:56 by kibotrel          #+#    #+#             */
/*   Updated: 2019/05/14 10:27:07 by reda-con         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "env.h"
#include "wolf3d.h"
#include <stdio.h>

void	change_angle(t_env *env, SDL_Keysym key)
{
	if (key.sym == SDLK_COMMA)
		env->cam.angle += 2 * RADIAN;
	else
		env->cam.angle -= 2 * RADIAN;
	printf("%f\n", env->cam.angle);
	raycast(env->map, env, &env->cam , &env->ray);
}
