/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 07:45:26 by nde-jesu          #+#    #+#             */
/*   Updated: 2019/05/24 16:03:55 by reda-con         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "wolf3d.h"

/*
static int		coll_wall(t_env *env, t_pos coord, char *key)
{
	if (env->map[(int)coord.y / CELL][(int)coord.x / CELL] == 1)
	{
		if (key == SDL_SCANCODE_W)
			move(env, oui, SDL_SCANCODE_S);
		if (key == SDL_SCANCODE_S)
			move(env, oui, SDL_SCANCODE_W);
		if (key == SDL_SCANCODE_A)
			move(env, oui, SDL_SCANCODE_D);
		if (key == SDL_SCANCODE_D)
			move(env, oui, SDL_SCANCODE_A);
		return (0);
	}
	return (1);
}
*/

void			move(t_env *env, char *key)
{
	if (key[SDL_SCANCODE_W])
	{
		env->cam.coord.x += cos(env->cam.angle) * 16;
		env->cam.coord.y -= sin(env->cam.angle) * 16;
	}
	if (key[SDL_SCANCODE_S])
	{
		env->cam.coord.x -= cos(env->cam.angle) * 16;
		env->cam.coord.y += sin(env->cam.angle) * 16;
	}
	if (key[SDL_SCANCODE_A])
	{
		env->cam.coord.x += cos(env->cam.angle + R_N) * 8;
		env->cam.coord.y -= sin(env->cam.angle + R_N) * 8;
	}
	if (key[SDL_SCANCODE_D])
	{
		env->cam.coord.x -= cos(env->cam.angle + R_N) * 8;
		env->cam.coord.y += sin(env->cam.angle + R_N) * 8;
	}
//	if (coll_wall(env, env->cam.coord, code, key))
		raycast(env->map, env, &env->cam, &env->ray);
}
