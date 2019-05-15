/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 07:45:26 by nde-jesu          #+#    #+#             */
/*   Updated: 2019/05/15 14:56:04 by reda-con         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "wolf3d.h"

int		coll_wall(t_env *env)
{
	if (env->map[(int)env->cam.coord.y/64][(int)env->cam.coord.x/64] == 1)
	{
		if (env->sdl.event.key.keysym.sym == SDLK_w)
			move_backward(env);
		else if (env->sdl.event.key.keysym.sym == SDLK_s)
			move_forward(env);
		else if (env->sdl.event.key.keysym.sym == SDLK_a)
			move_right(env);
		else if (env->sdl.event.key.keysym.sym == SDLK_d)
			move_left(env);
		return (0);
	}
	return (1);
}

void	move_forward(t_env *env)
{
	env->cam.coord.x += cos(env->cam.angle) * 10;
	env->cam.coord.y -= sin(env->cam.angle) * 10;
	if (coll_wall(env))
		raycast(env->map, env, &env->cam, &env->ray);
}

void	move_backward(t_env *env)
{
	env->cam.coord.x -= cos(env->cam.angle) * 10;
	env->cam.coord.y += sin(env->cam.angle) * 10;
	if (coll_wall(env))
		raycast(env->map, env, &env->cam, &env->ray);
}

void	move_left(t_env *env)
{
	env->cam.coord.x += cos(env->cam.angle + R_N) * 8;
	env->cam.coord.y -= sin(env->cam.angle + R_N) * 8;
	if (coll_wall(env))
		raycast(env->map, env, &env->cam, &env->ray);
}

void	move_right(t_env *env)
{
	env->cam.coord.x -= cos(env->cam.angle + R_N) * 8;
	env->cam.coord.y += sin(env->cam.angle + R_N) * 8;
	if (coll_wall(env))
		raycast(env->map, env, &env->cam, &env->ray);
}
