/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   true_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:30:34 by nde-jesu          #+#    #+#             */
/*   Updated: 2019/05/02 11:26:54 by reda-con         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "env.h"
#include "wolf3d.h"

#define SQUARE_SIZE 64
#include <stdio.h>
#include <unistd.h>

double	rad_angle(double angle)
{
	return (angle * M_PI / 180);
}

t_ptd	init_ptd(double x, double y)
{
	t_ptd	ret;

	ret.x = x;
	ret.y = y;
	return (ret);
}

float	my_tan(double angle)
{
	return (sin(angle) / cos(angle));
}

static t_ray_cast	init_rc(t_player play)
{
	t_ray_cast	ret;

	ret.distance_screen = (WIN_WIDTH / 2) / my_tan(rad_angle(30));
	if (play.play_angle < 30)
		ret.act_angle = play.play_angle + 330;
	else
		ret.act_angle = play.play_angle - 30;
	return (ret);
}

static t_player	init_player(void)
{
	t_player	ret;

	ret.play_pos.x = 1.5;
	ret.play_pos.y = 3.5;
	ret.play_coor.x = floor(ret.play_pos.x) * SQUARE_SIZE\
					+ (ret.play_pos.x - floor(ret.play_pos.x)) * SQUARE_SIZE;
	ret.play_coor.y = floor(ret.play_pos.y) * SQUARE_SIZE\
					+ (ret.play_pos.y - floor(ret.play_pos.y)) * SQUARE_SIZE;
	ret.play_angle = 60;
	ret.play_angle = (ret.play_angle == 360) ? 0 : ret.play_angle;
	return (ret);
}

static t_ray_cast	y_collisions(t_ray_cast all, t_player play)
{
	if (all.act_angle > 0 && all.act_angle < 180)
		all.coll_y.y = floor(play.play_coor.y / SQUARE_SIZE) * SQUARE_SIZE - 1;
	else
		all.coll_y.y = floor(play.play_coor.y / SQUARE_SIZE)\
					* SQUARE_SIZE + SQUARE_SIZE;
	all.dist_col_y.y = (all.act_angle > 0 && all.act_angle < 180)\
					? -SQUARE_SIZE : SQUARE_SIZE;
	all.coll_y.x = play.play_coor.x + (play.play_coor.y - all.coll_y.y)\
				/ my_tan(rad_angle(all.act_angle));
	all.dist_col_y.x = SQUARE_SIZE / my_tan(rad_angle(all.act_angle));
	all.dist_col_y.x = (all.act_angle < 90 || all.act_angle > 270)\
					? all.dist_col_y.x : -all.dist_col_y.x;
	return (all);
}

static t_ray_cast	x_collisions(t_ray_cast all, t_player play)
{
	if (all.act_angle < 90 || all.act_angle > 270)
		all.coll_x.x = floor(play.play_coor.x / SQUARE_SIZE)\
					* SQUARE_SIZE + SQUARE_SIZE;
	else
		all.coll_x.x = floor(play.play_coor.x / SQUARE_SIZE) * SQUARE_SIZE - 1;
	all.dist_col_x.x = (all.act_angle < 90 || all.act_angle > 270)\
					? SQUARE_SIZE : -SQUARE_SIZE;
	all.coll_x.y = play.play_coor.y + (play.play_coor.x - all.coll_x.x)\
				* my_tan(rad_angle(all.act_angle));
	all.dist_col_x.y = SQUARE_SIZE * my_tan(rad_angle(all.act_angle));
	all.dist_col_x.y = (all.act_angle > 0 && all.act_angle < 180)\
				? -(all.dist_col_x.y) : all.dist_col_x.y;
	return (all);
}

static t_ray_cast	check_coll(t_ray_cast all, int map[4][10])
{
	int		hit_x;
	int		hit_y;

	hit_x = 0;
	hit_y = 0;
	while (hit_x == 0 && hit_y == 0)
	{
		if (map[(int)all.coll_x.y / SQUARE_SIZE]\
				[(int)all.coll_x.x / SQUARE_SIZE] != 0 && hit_x == 0)
			hit_x = 1;
		else
		{
			all.coll_x.x += all.dist_col_x.x;
			all.coll_x.y += all.dist_col_x.y;
		}
		if (map[(int)all.coll_y.y / SQUARE_SIZE]\
				[(int)all.coll_y.x / SQUARE_SIZE] != 0 && hit_y == 0)
			hit_y = 1;
		else
		{
			all.coll_y.x += all.dist_col_y.x;
			all.coll_y.y += all.dist_col_y.y;
		}
	}
	return (all);
}

void		true_raycast(int map[4][10])
{
	int			x;
	t_player	play;
	t_ray_cast	all;

	x = -1;
	play = init_player();
	all = init_rc(play);
	while (++x < WIN_WIDTH)
	{
		all = y_collisions(all, play);
		all = x_collisions(all, play);
		all = check_coll(all, map);
		all.dist_col = sqrt(pow(all.coll_x.x / 64 - play.play_pos.x, 2)\
				+ pow(all.coll_x.y / 64 - play.play_pos.y, 2));
		if (all.dist_col > sqrt(pow(all.coll_y.x / 64 - play.play_pos.x, 2)\
					+ pow(all.coll_y.y / 64 - play.play_pos.y, 2)))
			all.dist_col = sqrt(pow(all.coll_y.x / 64 - play.play_pos.x, 2)\
					+ pow(all.coll_y.y / 64 - play.play_pos.y, 2));
		all.act_angle += 60.0 / WIN_WIDTH;
	}
}

int		main(void)
{
	int	worldMap[4][10]=
	{
		{1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1}
	};

	true_raycast(worldMap);
	return (0);
}
