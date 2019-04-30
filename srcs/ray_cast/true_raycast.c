/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   true_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:30:34 by nde-jesu          #+#    #+#             */
/*   Updated: 2019/04/30 07:46:38 by nde-jesu         ###   ########.fr       */
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

void	true_raycast(int map[4][10])
{
	t_ptd	play_pos = {2, 1};
	int		play_angle;
	double	angle_between_ray;
	double	distance_screen;
	//int 	x = -1; 
	t_ptd	dist_col;
	t_ptd	first_coll;
	t_ptd	truc;
	int		hit;

	hit = 0;
	distance_screen = (WIN_WIDTH / 2) / tan(rad_angle(30));
	angle_between_ray = 60 / WIN_WIDTH;
	play_angle = 269;
	truc.x = floor(play_pos.x) * SQUARE_SIZE + (play_pos.x - floor(play_pos.x)) * SQUARE_SIZE;
	truc.y = floor(play_pos.y) * SQUARE_SIZE + (play_pos.y - floor(play_pos.y)) * SQUARE_SIZE;
//	while (++x < WIN_WIDTH) // Pour chaque colonne de l'ecran
//	{
		// Pour les collisions en Y
		// Chercher premiere collisions avec un bord
		if (play_angle > 0 && play_angle < 180)
		{
			first_coll.y = floor(truc.y / SQUARE_SIZE) * SQUARE_SIZE - 1;
			dist_col.y = -SQUARE_SIZE;
		}
		else
		{
			first_coll.y = floor(truc.y / SQUARE_SIZE) * SQUARE_SIZE + SQUARE_SIZE;
			dist_col.y = SQUARE_SIZE;
		}
		// Chercher collision avec le mur
		first_coll.x = (truc.y - first_coll.y) / tan(rad_angle(play_angle)) + truc.x;
		dist_col.x = SQUARE_SIZE / tan(rad_angle(play_angle));
		while (hit == 0)
		{
			if (map[(int)first_coll.y / SQUARE_SIZE][(int)first_coll.x / SQUARE_SIZE] != 0)
			{
				hit = 1;
				//printf("%i\n", map[(int)next_coll.y / SQUARE_SIZE][(int)next_coll.x / SQUARE_SIZE]);
				printf(" Y :%i %i\n", (int)first_coll.x / SQUARE_SIZE, (int)first_coll.y / SQUARE_SIZE);
			} 
			first_coll.x += dist_col.x;
			first_coll.y += dist_col.y;
		}
		// Pour les collisions en X
		if (play_angle > 270 || play_angle < 90)
		{
			first_coll.x = floor(truc.x / SQUARE_SIZE) * SQUARE_SIZE + SQUARE_SIZE;
			dist_col.x = SQUARE_SIZE;
		}
		else
		{
			first_coll.x = floor(truc.x / SQUARE_SIZE) * SQUARE_SIZE - 1;
			dist_col.x = -SQUARE_SIZE;
		}

		first_coll.y = (truc.x - first_coll.x) * tan(rad_angle(play_angle)) + truc.y;
		dist_col.y = SQUARE_SIZE / tan(rad_angle(play_angle));
		hit = 0;
		printf("%f\n", first_coll.y);
		while (hit == 0)
		{
			write(1, "peut\n", 5);
			if (map[(int)first_coll.y / SQUARE_SIZE][(int)first_coll.x / SQUARE_SIZE] != 0)
			{
				write(1, "etre\n", 5);
				hit = 1;
				//printf("%i\n", map[(int)next_coll.y / SQUARE_SIZE][(int)next_coll.x / SQUARE_SIZE]);
				printf("X : %i %i\n", (int)first_coll.x / SQUARE_SIZE, (int)first_coll.y / SQUARE_SIZE);
			} 				
			write(1, "je\n", 3);
			first_coll.x += dist_col.x;
			first_coll.y += dist_col.y;
		}	
//	}
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