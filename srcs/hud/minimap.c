/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 17:07:29 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/13 01:41:51 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "env.h"
#include "wolf3d.h"

#include <stdio.h>

void	get_player_position(t_env *env, t_pos *player)
{
	player->x = env->cam.coord.x / 64 - floor(env->cam.coord.x / 64);
	player->y = env->cam.coord.y / 64 - floor(env->cam.coord.y / 64);
	player->x = (int)(map(player->x, fill_data(0, 1, 0, 32)));
	player->y = (int)(map(player->y, fill_data(0, 1, 0, 32)));
	player->x += (floor(env->cam.coord.x / 64) * 32) + 16;
	player->y += (floor(env->cam.coord.y / 64) * 32) + 16;
}

void	objects(t_env *env)
{
	t_pos	pos;
	t_pos	wall;
	t_pos	limit;

	pos.y = -1;
	while (++pos.y < env->height)
	{
		pos.x = -1;
		while (++pos.x < env->width)
		{
			wall.y = pos.y * 32 + 15;
			limit.y = wall.y + 32;
			limit.x = pos.x * 32 + 47;
			if (env->map[(int)pos.y][(int)pos.x] == 1)
				walls(&env->sdl, wall, limit, pos.x);
			else if (env->map[(int)pos.y][(int)pos.x] == 9)
				spawn(&env->sdl, wall, limit, pos.x);
			else if (env->map[(int)pos.y][(int)pos.x] == 5)
				end(&env->sdl, wall, limit, pos.x);
		}
	}
}

void	minimap(t_env *env)
{
	t_pos	map;
	t_pos	player;
	t_pos	pos;

	get_player_position(env, &player);
	map.y = -1;
	pos.y = player.y - 4;
	while (++map.y < env->height * 32 + 33)
	{
		map.x = -1;
		while (++map.x < env->width * 32 + 33)
			env->sdl.pixels[(int)(map.x + map.y * WIDTH)] = 0;
	}
	objects(env);
	while (++pos.y < player.y + 4)
	{
		pos.x = player.x - 4;
		while (++pos.x < player.x + 4)
			env->sdl.pixels[(int)(pos.x + pos.y * WIDTH)] = 0xff0000;
	}
}
