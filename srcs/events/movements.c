/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 07:45:26 by nde-jesu          #+#    #+#             */
/*   Updated: 2019/05/29 08:14:44 by nde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "wolf3d.h"

static int		coll_wall(t_env *env, t_pos coord, char *key)
{
	if (env->map[(int)coord.y / CELL][(int)coord.x / CELL] == 1)
	{
		if (key[SDL_SCANCODE_W])
			move_backward(env);
		if (key[SDL_SCANCODE_S])
			move_forward(env);
		if (key[SDL_SCANCODE_A])
			move_right(env);
		if (key[SDL_SCANCODE_D])
			move_left(env);
		return (0);
	}
	return (1);
}

void			move(t_env *env, char *key, int fl)
{
	if (key[SDL_SCANCODE_W] || fl == 1)
		move_forward(env);
	if (key[SDL_SCANCODE_S] || fl == 2)
		move_backward(env);
	if (key[SDL_SCANCODE_A] || fl == 3)
		move_left(env);
	if (key[SDL_SCANCODE_D] || fl == 4)
		move_right(env);
	coll_wall(env, env->cam.coord, key);
}