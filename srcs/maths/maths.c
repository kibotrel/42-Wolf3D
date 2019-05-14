/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 16:04:04 by kibotrel          #+#    #+#             */
/*   Updated: 2019/05/14 17:42:01 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
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

double					length(t_pos hit_x, t_pos hit_y, t_pos coord)
{
	double	is_y;
	double	is_x;

	is_x = sqrt(pow2(hit_x.x - coord.x) + pow2(hit_x.y - coord.y));
	is_y = sqrt(pow2(hit_y.x - coord.x) + pow2(hit_y.y - coord.y));
	return (is_x > is_y ? is_y : is_x);
}
