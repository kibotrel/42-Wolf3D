/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 07:45:26 by nde-jesu          #+#    #+#             */
/*   Updated: 2019/05/22 17:08:10 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "wolf3d.h"

static int		coll_wall(t_env *env, t_pos coord, SDL_Keycode key)
{
	if (env->map[(int)coord.y / CELL][(int)coord.x / CELL] == 1)
	{
		if (key == SDLK_w)
			move(env, SDLK_s);
		else if (key == SDLK_s)
			move(env, SDLK_w);
		else if (key == SDLK_a)
			move(env, SDLK_d);
		else if (key == SDLK_d)
			move(env, SDLK_a);
		return (0);
	}
	return (1);
}

void	move(t_env *env, SDL_Keycode key)
{
	if (key == SDLK_w)
	{
		env->cam.coord.x += cos(env->cam.angle) * 16;
		env->cam.coord.y -= sin(env->cam.angle) * 16;
	}
	else if (key == SDLK_s)
	{
		env->cam.coord.x -= cos(env->cam.angle) * 16;
		env->cam.coord.y += sin(env->cam.angle) * 16;
	}
	else if (key == SDLK_a)
	{
		env->cam.coord.x += cos(env->cam.angle + R_N) * 8;
		env->cam.coord.y -= sin(env->cam.angle + R_N) * 8;
	}
	else
	{
		env->cam.coord.x -= cos(env->cam.angle + R_N) * 8;
		env->cam.coord.y += sin(env->cam.angle + R_N) * 8;
	}
	if (coll_wall(env, env->cam.coord, key))
		raycast(env->map, env, &env->cam, &env->ray);
}
