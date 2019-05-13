/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 18:16:08 by kibotrel          #+#    #+#             */
/*   Updated: 2019/05/13 17:52:08 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "env.h"
#include "wolf3d.h"

void	y_collisions(t_pos *hit_y, t_pos *gap_y, double angle, t_cam cam)
{
	if (angle > R_E && angle < R_W)
		hit_y->y = (int)(cam.coord.y / CELL) * CELL - 1;
	else
		hit_y->y = (int)(cam.coord.y / CELL) * CELL + CELL;
	gap_y->y = (angle > R_E && angle < R_W) ? -CELL : CELL;
	hit_y->x = cam.coord.x + (cam.coord.y - hit_y->y) / tan(angle);
	gap_y->x = CELL / tan(angle);
	gap_y->x = (angle > R_W && angle < R_S) ? -gap_y->x : gap_y->x;
}

void	x_collisions(t_pos *hit_x, t_pos *gap_x, double angle, t_cam cam)
{
	if (angle < R_N || angle > R_S)
		hit_x->x = (int)(cam.coord.x / CELL) * CELL + CELL;
	else
		hit_x->x = (int)(cam.coord.x / CELL) * CELL - 1;
	gap_x->x = (angle < R_N || angle > R_S) ? CELL : -CELL;
	hit_x->y = cam.coord.y + (cam.coord.x - hit_x->x) * tan(angle);
	gap_x->y = CELL * tan(angle);
	gap_x->y = (angle > R_E && angle < R_N) ? -gap_x->y : gap_x->y;
}
