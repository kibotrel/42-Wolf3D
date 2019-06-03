/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 07:45:26 by nde-jesu          #+#    #+#             */
/*   Updated: 2019/06/03 13:10:45 by reda-con         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "wolf3d.h"

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
