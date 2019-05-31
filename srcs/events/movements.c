/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 07:45:26 by nde-jesu          #+#    #+#             */
/*   Updated: 2019/05/31 14:32:04 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "wolf3d.h"

void			move_forward(t_env *env, t_cam cam)
{
	env->cam.coord.x += cos(radians(env->cam.angle)) * (8 * cam.sprint);
	env->cam.coord.y -= sin(radians(env->cam.angle)) * (8 * cam.sprint);
}

void			move_backward(t_env *env, t_cam cam)
{
	env->cam.coord.x -= cos(radians(env->cam.angle)) * (8 * cam.sprint);
	env->cam.coord.y += sin(radians(env->cam.angle)) * (8 * cam.sprint);
}

void			move_left(t_env *env, t_cam cam)
{
	env->cam.coord.x += cos(radians(env->cam.angle + 90)) * (8 * cam.sprint);
	env->cam.coord.y -= sin(radians(env->cam.angle + 90)) * (8 * cam.sprint);
}

void			move_right(t_env *env, t_cam cam)
{
	env->cam.coord.x -= cos(radians(env->cam.angle + 90)) * (8 * cam.sprint);
	env->cam.coord.y += sin(radians(env->cam.angle + 90)) * (8 * cam.sprint);
}

static void		coll_wall(t_env *env, t_pos coord, char *key)
{
	if (env->map[(int)coord.y / CELL][(int)coord.x / CELL] == 1)
	{
		if (key[SDL_SCANCODE_W])
			move_backward(env, env->cam);
		if (key[SDL_SCANCODE_S])
			move_forward(env, env->cam);
		if (key[SDL_SCANCODE_A])
			move_right(env, env->cam);
		if (key[SDL_SCANCODE_D])
			move_left(env, env->cam);
	}
}

void			move(t_env *env, char *key)
{
	if (key[SDL_SCANCODE_W])
		move_forward(env, env->cam);
	if (key[SDL_SCANCODE_S])
		move_backward(env, env->cam);
	if (key[SDL_SCANCODE_A])
		move_left(env, env->cam);
	if (key[SDL_SCANCODE_D])
		move_right(env, env->cam);
	coll_wall(env, env->cam.coord, key);
}
