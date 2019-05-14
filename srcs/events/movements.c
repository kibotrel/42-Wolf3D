/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 07:45:26 by nde-jesu          #+#    #+#             */
/*   Updated: 2019/05/14 10:41:50 by reda-con         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "wolf3d.h"

void	move_forward(t_env *env, int neg)
{
	neg = ((env->cam.angle < R_N && env->cam.angle > R_E)
		|| (env->cam.angle > R_W && env->cam.angle < R_S)) ? -1 : 1;
	env->cam.coord.x += cos(env->cam.angle) * 16 * neg;
	env->cam.coord.y -= sin(env->cam.angle) * 16;
	raycast(env->map, env, &env->cam, &env->ray);
}

void	move_backward(t_env *env, int neg)
{
	neg = ((env->cam.angle < R_N && env->cam.angle > R_E)
		|| (env->cam.angle > R_W && env->cam.angle < R_S)) ? -1 : 1;
	env->cam.coord.x -= cos(env->cam.angle) * 16 * neg;
	env->cam.coord.y += sin(env->cam.angle) * 16;
	raycast(env->map, env, &env->cam, &env->ray);
}

void	move_left(t_env *env, int neg)
{
	neg = ((env->cam.angle + R_N < R_N && env->cam.angle + R_N > R_E)
		|| (env->cam.angle + R_N > R_W && env->cam.angle + R_N < R_S)) ? -1 : 1;
	env->cam.coord.x += cos(env->cam.angle + R_N) * 10;
	env->cam.coord.y -= sin(env->cam.angle + R_N) * 10;
	raycast(env->map, env, &env->cam, &env->ray);
}

void	move_right(t_env *env, int neg)
{
	neg = ((env->cam.angle + R_N < R_N && env->cam.angle + R_N > R_E)
		|| (env->cam.angle + R_N > R_W && env->cam.angle + R_N < R_S)) ? -1 : 1;
	env->cam.coord.x -= cos(env->cam.angle + R_N) * 10;
	env->cam.coord.y += sin(env->cam.angle + R_N) * 10;
	raycast(env->map, env, &env->cam, &env->ray);
}
