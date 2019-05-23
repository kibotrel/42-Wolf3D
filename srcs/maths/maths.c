/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 16:04:04 by kibotrel          #+#    #+#             */
/*   Updated: 2019/05/23 10:51:41 by reda-con         ###   ########.fr       */
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
			ray->wall.color = 0xff33c47f;
		else
			ray->wall.color = 0xffff6950;
		return (is_y);
	}
	else
	{
		if (ray->angle > R_N && ray->angle < R_S)
			ray->wall.color = 0xff1c4f99;
		else
			ray->wall.color = 0xffa061d1;
		return (is_x);
	}
}
