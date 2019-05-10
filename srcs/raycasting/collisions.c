/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 18:16:08 by kibotrel          #+#    #+#             */
/*   Updated: 2019/05/10 18:47:25 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "env.h"
#include "wolf3d.h"

void	y_collisions(t_ray_cast *all, t_player *play)
{
	if (all->act_angle > R_E && all->act_angle < R_O)
		all->coll_y.y = (int)(play->play_coor.y / SQUARE_SIZE) * SQUARE_SIZE - 1;
	else
		all->coll_y.y = (int)(play->play_coor.y / SQUARE_SIZE) * SQUARE_SIZE + SQUARE_SIZE;
	all->dist_col_y.y = (all->act_angle > R_E && all->act_angle < R_O) ? -SQUARE_SIZE : SQUARE_SIZE;
	all->coll_y.x = play->play_coor.x + (play->play_coor.y - all->coll_y.y) / tan(all->act_angle);
	all->dist_col_y.x = SQUARE_SIZE / tan(all->act_angle);
	all->dist_col_y.x = (all->act_angle > R_O && all->act_angle < R_S) ? -all->dist_col_y.x : all->dist_col_y.x;
}

void	x_collisions(t_ray_cast *all, t_player *play)
{
	if (all.act_angle < R_N || all.act_angle > R_S)
		all.coll_x.x = (int)(play->play_coor.x / SQUARE_SIZE) * SQUARE_SIZE + SQUARE_SIZE;
	else
		all.coll_x.x = (int)(play->play_coor.x / SQUARE_SIZE) * SQUARE_SIZE - 1;
	all.dist_col_x.x = (all.act_angle < R_N || all.act_angle > R_S) ? SQUARE_SIZE : -SQUARE_SIZE;
	all.coll_x.y = play->play_coor.y + (play->play_coor.x - all.coll_x.x) * tan((all.act_angle);
	all.dist_col_x.y = SQUARE_SIZE * tan(all.act_angle);
	all.dist_col_x.y = (all.act_angle > R_E && all.act_angle < R_N) ? -(all.dist_col_x.y) : all.dist_col_x.y;
}
