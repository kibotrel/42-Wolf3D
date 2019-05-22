/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_blocks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 10:00:19 by nde-jesu          #+#    #+#             */
/*   Updated: 2019/05/22 16:59:41 by reda-con         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "env.h"

static void		is_block(int **map, t_pos *coord, int new_x, int new_y)
{
	int block;

	block = 2;
	if (map[(int)(coord->y / CELL) + new_y][(int)coord->x / CELL + new_x] == 1)
		return ;
	if(map[(int)(coord->y / CELL) + new_y][(int)coord->x / CELL + new_x] == 2)
		block = 0;
	map[(int)(coord->y / CELL) + new_y][(int)coord->x / CELL + new_x] = block;
}

void		place_block(t_env *env)
{
	double angle = env->cam.angle;
	
	if (angle > 2 * M_PI / 6 && angle <= 4 * M_PI / 6)
		is_block(env->map, &env->cam.coord, 0, -1);
	else if (angle > 4* M_PI / 6 && angle <= 5 * M_PI / 6)
		is_block(env->map, &env->cam.coord, -1, -1);
	else if (angle > 5 * M_PI / 6 && angle <= 7 * M_PI / 6)
		is_block(env->map, &env->cam.coord, -1, 0);
	else if (angle > 7 * M_PI / 6 && angle <= 8 * M_PI / 6)
		is_block(env->map, &env->cam.coord, -1, 1);
	else if (angle > 8 * M_PI / 6 && angle <= 10 * M_PI / 6)
		is_block(env->map, &env->cam.coord, 0, 1);
	else if (angle > 10 * M_PI / 6 && angle <= 11 * M_PI / 6)
		is_block(env->map, &env->cam.coord, 1, 1);
	else if (angle > 11 * M_PI / 6 && angle <= 13 * M_PI / 6)
		is_block(env->map, &env->cam.coord, 1, 0);
	else
		is_block(env->map, &env->cam.coord, 1, -1);
	raycast(env->map, env, &env->cam, &env->ray);
}
