/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 16:04:04 by kibotrel          #+#    #+#             */
/*   Updated: 2019/05/22 17:18:50 by kibotrel         ###   ########.fr       */
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

double					length(t_pos col_x, t_pos col_y, t_pos coord, t_ray *ray)
{
	double	is_y;
	double	is_x;

	is_x = sqrt(pow(col_x.x - coord.x, 2) + pow(col_x.y - coord.y, 2));
	is_y = sqrt(pow(col_y.x - coord.x, 2) + pow(col_y.y - coord.y, 2));
	if (is_x > is_y)
	{
		if (ray->angle > R_E && ray->angle < R_W)
			ray->wall.color = 0x33c47fff;
		else
			ray->wall.color = 0xff6950ff;
		return (is_y);
	}
	else
	{
		if (ray->angle > R_N && ray->angle < R_S)
			ray->wall.color = 0x1c4f99ff;
		else
			ray->wall.color = 0xa061d1ff;
		return (is_x);
	}
}
