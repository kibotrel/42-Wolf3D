/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 16:04:04 by kibotrel          #+#    #+#             */
/*   Updated: 2019/05/30 15:10:13 by kibotrel         ###   ########.fr       */
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
		if (ray->angle > R_E && ray->angle < R_W)
			ray->which_wall = 0;
		else
			ray->which_wall = 1;
		ray->offset = (int)col_y.x % CELL;
		return (is_y);
	}
	else
	{
		if (ray->angle > R_N && ray->angle < R_S)
			ray->which_wall = 2;
		else
			ray->which_wall = 3;
		ray->offset = (int)col_x.y % CELL;
		return (is_x);
	}
}
