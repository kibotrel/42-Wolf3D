/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 17:07:29 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/03 10:46:32 by reda-con         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "wolf3d.h"

#include <stdio.h>

void	get_player_position(t_env *env)
{
	t_pos	tmp;

	tmp.x = env->cam.coord.x - (int)env->cam.coord.x;
	tmp.y = env->cam.coord.y - (int)env->cam.coord.y;

	// printf("%f,%f\n", tmp.y, tmp.x);
}

void	walls(t_env *env)
{
	int		x;
	int		y;
	t_pos	wall;
	t_pos	limit;

	y = -1;

	while (++y < env->height)
	{
		x = -1;
		while (++x < env->width)
		{
			if (env->map[y][x] == 1)
			{
				wall.y = y * 32 + 15;
				limit.y = wall.y + 32;
				limit.x = x * 32 + 47;
				while (++wall.y < limit.y)
				{
					wall.x = x * 32 + 15;
					while (++wall.x < limit.x)
						env->sdl.pixels[(int)(wall.x + wall.y * WIDTH)] = 0xffffff;
				}
			}
			if (env->map[y][x] == 9)
			{
				wall.y = y * 32 + 15;
				limit.y = wall.y + 32;
				limit.x = x * 32 + 47;
				while (++wall.y < limit.y)
				{
					wall.x = x * 32 + 15;
					while (++wall.x < limit.x)
						env->sdl.pixels[(int)(wall.x + wall.y * WIDTH)] = 0xffff00ff;
				}
			}
			if (env->map[y][x] == 5)
			{
				wall.y = y * 32 + 15;
				limit.y = wall.y + 32;
				limit.x = x * 32 + 47;
				while (++wall.y < limit.y)
				{
					wall.x = x * 32 + 15;
					while (++wall.x < limit.x)
						env->sdl.pixels[(int)(wall.x + wall.y * WIDTH)] = 0xff7fffff;
				}
			}
		}
	}
}

void	minimap(t_env *env)
{
	t_pos	map;
	t_pos	player;
	t_pos	limit;

	get_player_position(env);
	map.y = -1;
	player.y = (floor(floor(env->cam.coord.y) / 64) * 32 + 23);
	limit.x = (floor(floor(env->cam.coord.x) / 64) + 1) * 32 + 8;
	limit.y = (floor(floor(env->cam.coord.y) / 64) + 1) * 32 + 8;
	while (++map.y < env->height * 32 + 33)
	{
		map.x = -1;
		while (++map.x < env->width * 32 + 33)
			env->sdl.pixels[(int)(map.x + map.y * WIDTH)] = 0;
	}
	walls(env);
	while (++player.y < limit.y)
	{
		player.x = (floor(floor(env->cam.coord.x) / 64) * 32 + 23);
		while (++player.x < limit.x)
			env->sdl.pixels[(int)(player.x + player.y * WIDTH)] = 0xff0000;
	}

}
