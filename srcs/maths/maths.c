/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 16:04:04 by kibotrel          #+#    #+#             */
/*   Updated: 2019/05/28 23:56:30 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "env.h"
#include "wolf3d.h"

double	radians(double angle)
{
	return (angle * M_PI / 180);
}

double	smallest_distance(t_ray *ray, t_data data, t_pos coord)
{
	double	y;
	double	x;

	x = fabs(fabs(coord.x - ray->hit_x.x) / cos(ray->angle));
	y = fabs(fabs(coord.x - ray->hit_y.x) / cos(ray->angle));
	if (x > y)
	{
		if (ray->angle > 0 && ray->angle < M_PI)
			ray->wall.color = WALL_ALLIANCE;
		else
			ray->wall.color = WALL_ORDER;
		return (y);
	}
	else
	{
		if (ray->angle > data.north && ray->angle < data.south)
			ray->wall.color = WALL_FEDERATION;
		else
			ray->wall.color = WALL_ASSEMBLY;
		return (x);
	}
}
