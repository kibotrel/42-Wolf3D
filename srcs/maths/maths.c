/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 16:04:04 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/03 14:21:04 by reda-con         ###   ########.fr       */
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
			ray->which_wall = 0;
		else
			ray->which_wall = 1;
		ray->offset = (int)ray->hit_y.x % CELL + 1;
		return (y);
	}
	else
	{
		if (ray->angle > data.north && ray->angle < data.south)
			ray->which_wall = 2;
		else
			ray->which_wall = 3;
		ray->offset = (int)ray->hit_x.y % CELL + 1;
		return (x);
	}
}
