/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teleport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 15:09:44 by kibotrel          #+#    #+#             */
/*   Updated: 2019/07/10 15:26:14 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"
#include "env.h"
#include "wolf3d.h"

void	teleport_player(t_env *env, t_pos pos)
{
	pos.x = floor(pos.x / CELL);
	pos.y = floor(pos.y / CELL);
	if (pos.x == env->tp_start[0].x && pos.y == env->tp_start[0].y)
	{
		env->cam.coord = env->tp_end[1].pos;
		env->cam.angle = env->tp_end[1].angle;
	}
	if (pos.x == env->tp_start[1].x && pos.y == env->tp_start[1].y)
	{
		env->cam.coord = env->tp_end[0].pos;
		env->cam.angle = env->tp_end[0].angle;
	}
}
