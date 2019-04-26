/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 14:57:54 by kibotrel          #+#    #+#             */
/*   Updated: 2019/04/26 14:16:16 by reda-con         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "env.h"
#include "wolf3d.h"
#include "SDL.h"

t_ray_cast	dda(int map[4][10], t_ray_cast all)
{
	int		hit;

	all.wall_side = 0;
	hit = 0;
	while (hit == 0)
	{
		if (all.len_next_side.x < all.len_next_side.y)
		{
			all.len_next_side.x += all.delta_dist.x;
			all.map_co.x += all.step.x;
			all.wall_side = 0;
		}
		else
		{
			all.len_next_side.y += all.delta_dist.y;
			all.map_co.y += all.step.y;
			all.wall_side = 1;
		}
		if (map[all.map_co.x][all.map_co.y] > 0)
			hit = 1;
	}
	return (all);
}

t_ray_cast	init_rc(t_ray_cast all, int x, t_ptd play_pos, t_ptd play_vec)
{
	if (x == 0)
	{
		all.cam_plane.x = 0;
		all.cam_plane.y = 0.66;
	}
	all.cam_x = 2 * x / (double)WIN_WIDTH - 1;
	all.ray_dir.x = play_vec.x + all.cam_plane.x * all.cam_x;
	all.ray_dir.y = play_vec.y + all.cam_plane.y * all.cam_x;
	all.map_co.x = (int)play_pos.x;
	all.map_co.y = (int)play_pos.y;
	all.delta_dist.x = double_abs(1 / all.ray_dir.x);
	all.delta_dist.y = double_abs(1 / all.ray_dir.y);
	return (all);
}

t_ray_cast	norme1(t_ray_cast all, t_ptd play_pos)
{
	if (all.ray_dir.x < 0)
	{
		all.step.x = -1;
		all.len_next_side.x = (play_pos.x - all.map_co.x) * all.delta_dist.x;
	}
	else
	{
		all.step.x = 1;
		all.len_next_side.x =\
						(all.map_co.x + 1.0 - play_pos.x) * all.delta_dist.x;
	}
	if (all.ray_dir.y < 0)
	{
		all.step.y = -1;
		all.len_next_side.y = (play_pos.y - all.map_co.y) * all.delta_dist.y;
	}
	else
	{
		all.step.y = 1;
		all.len_next_side.y =\
						(all.map_co.y + 1.0 - play_pos.y) * all.delta_dist.y;
	}
	return (all);
}

t_ray_cast	draw(t_ray_cast all, SDL_Renderer *ren, int map[4][10], int x)
{
	all.line_height = (int)(WIN_HEIGHT / all.wall_dist);
	all.line_draw.x = -all.line_height / 2 + WIN_HEIGHT / 2;
	all.line_draw.y = all.line_height / 2 + WIN_HEIGHT / 2;
	if (all.line_draw.x < 0)
		all.line_draw.x = 0;
	if (all.line_draw.y > WIN_HEIGHT)
		all.line_draw.y = WIN_HEIGHT - 1;
	check_wall_color(ren, map[all.map_co.x][all.map_co.y], all.wall_side);
	SDL_RenderDrawLine(ren, x, all.line_draw.x, x, all.line_draw.y);
	return (all);
}

void		raycast(SDL_Renderer *ren, int map[4][10], t_ptd play_pos, t_ptd play_vec)
{
	t_ray_cast	all;
	int			x;

	x = -1;
	while (++x < WIN_WIDTH)
	{
		all = init_rc(all, x, play_pos, play_vec);
		all = norme1(all, play_pos);
		all = dda(map, all);
		if (all.wall_side == 0)
			all.wall_dist = (all.map_co.x - play_pos.x + (1 - all.step.x) / 2)\
							/ all.ray_dir.x;
		else
			all.wall_dist = (all.map_co.y - play_pos.y + (1 - all.step.y) / 2)\
							/ all.ray_dir.y;
		all = draw(all, ren, map, x);
	}
}
