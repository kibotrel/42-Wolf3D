/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   true_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:30:34 by nde-jesu          #+#    #+#             */
/*   Updated: 2019/04/30 15:55:18 by reda-con         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "env.h"
#include "wolf3d.h"

#define SQUARE_SIZE 64
#include <stdio.h>

double rad_angle(double angle)
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

#include <unistd.h>

float	my_tan(double angle)
{
	return (sin(angle) / cos(angle));
}

void	true_raycast(int map[4][10])
{
	t_ptd	play_pos = {1.5, 3.5};
	int		play_angle;
	double	distance_screen;
	int 	x = -1; 
	t_ptd	dist_col_x;
	t_ptd	dist_col_y;
	t_ptd	coll_x;
	t_ptd	coll_y;
	t_ptd	play_coor;
	int		hit_x;
	int		hit_y;
	double	dist_col;
	double	act_angle;

	hit_x = 0;
	hit_y = 0;
	distance_screen = (WIN_WIDTH / 2) / my_tan(rad_angle(30));
	play_angle = 60;
	play_coor.x = floor(play_pos.x) * SQUARE_SIZE + (play_pos.x - floor(play_pos.x)) * SQUARE_SIZE;
	play_coor.y = floor(play_pos.y) * SQUARE_SIZE + (play_pos.y - floor(play_pos.y)) * SQUARE_SIZE;
	play_angle = (play_angle == 360) ? 0 : play_angle;
	if (play_angle < 30)
		act_angle = play_angle + 330;
	else
		act_angle = play_angle - 30;

	while (++x < WIN_WIDTH) // Pour chaque colonne de l'ecran
	{
		// Pour les collisions en Y
		// Chercher premiere collisions avec un bord
		if (act_angle > 0 && act_angle < 180)
			coll_y.y = floor(play_coor.y / SQUARE_SIZE) * SQUARE_SIZE - 1;
		else
			coll_y.y = floor(play_coor.y / SQUARE_SIZE) * SQUARE_SIZE + SQUARE_SIZE;
		dist_col_y.y = (act_angle > 0 && act_angle < 180) ? -SQUARE_SIZE : SQUARE_SIZE;
		// Chercher collision avec le mur
		coll_y.x = play_coor.x + (play_coor.y - coll_y.y) / my_tan(rad_angle(act_angle));
		dist_col_y.x = (act_angle < 90 || act_angle > 270) \
					   ? SQUARE_SIZE / my_tan(rad_angle(act_angle)) : -(SQUARE_SIZE / my_tan(rad_angle(act_angle)));



		// Pour les collisions en X
		if (act_angle < 90 || act_angle > 270)
			coll_x.x = floor(play_coor.x / SQUARE_SIZE) * SQUARE_SIZE + SQUARE_SIZE;
		else
			coll_x.x = floor(play_coor.x / SQUARE_SIZE) * SQUARE_SIZE - 1;
		dist_col_x.x = (act_angle < 90 || act_angle > 270) ? SQUARE_SIZE : -SQUARE_SIZE;
		coll_x.y = play_coor.y + (play_coor.x - coll_x.x) * my_tan(rad_angle(act_angle));
		dist_col_x.y = (act_angle > 0 && act_angle < 180) \
					   ? -(SQUARE_SIZE * my_tan(rad_angle(act_angle))) : SQUARE_SIZE * my_tan(rad_angle(act_angle));



		while (hit_x == 0 && hit_y == 0)
		{
			if (map[(int)coll_x.y / SQUARE_SIZE][(int)coll_x.x / SQUARE_SIZE] != 0 && hit_x == 0)
				hit_x = 1;
			else
			{
				coll_x.x += dist_col_x.x;
				coll_x.y += dist_col_x.y;
			}
			if (map[(int)coll_y.y / SQUARE_SIZE][(int)coll_y.x / SQUARE_SIZE] != 0 && hit_y == 0)
				hit_y = 1;
			else
			{
				coll_y.x += dist_col_y.x;
				coll_y.y += dist_col_y.y;
			}
		}



		dist_col = sqrt(pow(coll_x.x/64 - play_pos.x, 2) + pow(coll_x.y/64 - play_pos.y, 2));
		if (dist_col > sqrt(pow(coll_y.x/64 - play_pos.x, 2) + pow(coll_y.y/64 - play_pos.y, 2)))
			dist_col = sqrt(pow(coll_y.x/64 - play_pos.x, 2) + pow(coll_y.y/64 - play_pos.y, 2));
		printf("X: %f; %f ", coll_x.x/64, coll_x.y/64);
		printf("Y: %f; %f ", coll_y.x/64, coll_y.y/64);
		printf("DISTANCE DE TA RACE: %f\n", dist_col);
		act_angle += 60.0 / WIN_WIDTH;
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
