/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 07:45:26 by nde-jesu          #+#    #+#             */
/*   Updated: 2019/05/15 13:37:24 by reda-con         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "wolf3d.h"

void	move_forward(t_env *env)
{
	env->cam.coord.x += cos(env->cam.angle) * 10;
	env->cam.coord.y -= sin(env->cam.angle) * 10;
	raycast(env->map, env, &env->cam, &env->ray);
}

void	move_backward(t_env *env)
{
	env->cam.coord.x -= cos(env->cam.angle) * 6;
	env->cam.coord.y += sin(env->cam.angle) * 6;
	raycast(env->map, env, &env->cam, &env->ray);
}

void	move_left(t_env *env)
{
	env->cam.coord.x += cos(env->cam.angle + R_N) * 8;
	env->cam.coord.y -= sin(env->cam.angle + R_N) * 8;
	raycast(env->map, env, &env->cam, &env->ray);
}

void	move_right(t_env *env)
{
	env->cam.coord.x -= cos(env->cam.angle + R_N) * 8;
	env->cam.coord.y += sin(env->cam.angle + R_N) * 8;
	raycast(env->map, env, &env->cam, &env->ray);
}
