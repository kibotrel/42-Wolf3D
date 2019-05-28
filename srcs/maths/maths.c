/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 16:04:04 by kibotrel          #+#    #+#             */
/*   Updated: 2019/05/28 10:03:58 by nde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "env.h"
#include "wolf3d.h"

extern inline double	to_rad(double angle)
{
	return (angle * M_PI / 180);
}

double					double_abs(double i)
{
	return ((i > 0) ? i : -i);
}

double					pow2(double n)
{
	return (n * n);
}

double					length(t_pos col_x, t_pos col_y, t_pos coor, t_ray *ray)
{
	double	is_y;
	double	is_x;

	is_x = sqrt(pow(col_x.x - coor.x, 2) + pow(col_x.y - coor.y, 2));
	is_y = sqrt(pow(col_y.x - coor.x, 2) + pow(col_y.y - coor.y, 2));
	if (is_x > is_y)
	{
		if (ray->angle > R_E && ray->angle < R_W)
			ray->what_wall = 0;
		else
			ray->what_wall = 1;
		return (is_y);
	}
	else
	{
		if (ray->angle > R_N && ray->angle < R_S)
			ray->what_wall = 2;
		else
			ray->what_wall = 3;
		return (is_x);
	}
}
