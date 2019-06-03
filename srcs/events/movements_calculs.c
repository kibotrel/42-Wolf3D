/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_calculs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reda-con <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 13:09:32 by reda-con          #+#    #+#             */
/*   Updated: 2019/06/03 13:13:46 by reda-con         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <math.h>

void	move_forward(t_env *env, t_cam cam)
{
	env->cam.coord.x += cos(radians(env->cam.angle)) * (8 * cam.sprint);
	env->cam.coord.y -= sin(radians(env->cam.angle)) * (8 * cam.sprint);
}

void	move_backward(t_env *env, t_cam cam)
{
	env->cam.coord.x -= cos(radians(env->cam.angle)) * (8 * cam.sprint);
	env->cam.coord.y += sin(radians(env->cam.angle)) * (8 * cam.sprint);
}

void	move_left(t_env *env, t_cam cam)
{
	env->cam.coord.x += cos(radians(env->cam.angle + 90)) * (8 * cam.sprint);
	env->cam.coord.y -= sin(radians(env->cam.angle + 90)) * (8 * cam.sprint);
}

void	move_right(t_env *env, t_cam cam)
{
	env->cam.coord.x -= cos(radians(env->cam.angle + 90)) * (8 * cam.sprint);
	env->cam.coord.y += sin(radians(env->cam.angle + 90)) * (8 * cam.sprint);
}
