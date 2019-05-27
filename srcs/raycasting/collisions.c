/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 18:16:08 by kibotrel          #+#    #+#             */
/*   Updated: 2019/05/27 17:17:18 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "env.h"
#include "wolf3d.h"

void		y_collisions(t_ray *ray, t_cam cam, t_data data)
{
	if (ray->angle > data.east && ray->angle < data.west)
		ray->hit_y.y = floor(cam.coord.y / CELL) * CELL - 0.0000001;
	else
		ray->hit_y.y = floor(cam.coord.y / CELL) * CELL + CELL;
	ray->gap_y.y = (ray->angle > data.east && ray->angle < data.west) ? -CELL : CELL;
	ray->hit_y.x = cam.coord.x + (cam.coord.y - ray->hit_y.y) / tan(ray->angle);
	ray->gap_y.x = CELL / tan(ray->angle);
	ray->gap_y.x = (ray->angle > data.east && ray->angle < data.west ? ray->gap_y.x : -ray->gap_y.x);
}

void		x_collisions(t_ray *ray, t_cam cam, t_data data)
{
	if (ray->angle > data.north && ray->angle < data.south)
		ray->hit_x.x = floor(cam.coord.x / CELL) * CELL - 0.0000001;
	else
		ray->hit_x.x = floor(cam.coord.x / CELL) * CELL + CELL;
	ray->gap_x.x = (ray->angle > data.north && ray->angle < data.south) ? -CELL : CELL;
	ray->hit_x.y = cam.coord.y + (cam.coord.x - ray->hit_x.x) * tan(ray->angle);
	ray->gap_x.y = CELL * tan(ray->angle);
	ray->gap_x.y = (ray->angle > data.north && ray->angle < data.south ? ray->gap_x.y : -ray->gap_x.y);
}
