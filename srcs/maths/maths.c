/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 16:04:04 by kibotrel          #+#    #+#             */
/*   Updated: 2019/05/27 17:31:35 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "env.h"
#include "wolf3d.h"

double	radians(double angle)
{
	return (angle * M_PI / 180);
}

double	length(t_pos col_x, t_pos col_y, t_pos coord, t_env *env)
{
	double	is_y;
	double	is_x;

	is_x = fabs(fabs(coord.x - col_x.x) / cos(env->ray.angle));
	is_y = fabs(fabs(coord.x - col_y.x) / cos(env->ray.angle));
	if (is_x > is_y)
	{
		if (env->ray.angle > env->data.east && env->ray.angle < env->data.west)
			env->ray.wall.color = 0xff33c47f;
		else
			env->ray.wall.color = 0xffff6950;
		return (is_y);
	}
	else
	{
		if (env->ray.angle > env->data.north && env->ray.angle < env->data.south)
			env->ray.wall.color = 0xff1c4f99;
		else
			env->ray.wall.color = 0xffa061d1;
		return (is_x);
	}
}
