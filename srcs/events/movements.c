/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 07:45:26 by nde-jesu          #+#    #+#             */
/*   Updated: 2019/05/14 16:44:15 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "wolf3d.h"

void	move_forward(t_env *env, t_cam *cam)
{
	cam->coord.x += cos(cam->angle) * 16;
	cam->coord.y -= sin(cam->angle) * 16;
	raycast(env->map, env, cam, &env->ray);
}

void	move_backward(t_env *env, t_cam *cam)
{
	cam->coord.x -= cos(cam->angle) * 16;
	cam->coord.y += sin(cam->angle) * 16;
	raycast(env->map, env, cam, &env->ray);
}

void	move_left(t_env *env, t_cam *cam)
{

	cam->coord.x += cos(cam->angle + R_N) * 10;
	cam->coord.y -= sin(cam->angle + R_N) * 10;
	raycast(env->map, env, cam, &env->ray);
}

void	move_right(t_env *env, t_cam *cam)
{
	cam->coord.x -= cos(cam->angle + R_N) * 10;
	cam->coord.y += sin(cam->angle + R_N) * 10;
	raycast(env->map, env, cam, &env->ray);
}
