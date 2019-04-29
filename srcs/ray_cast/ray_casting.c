/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 14:57:54 by kibotrel          #+#    #+#             */
/*   Updated: 2019/04/29 11:11:27 by nde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "env.h"
#include "wolf3d.h"
#include "SDL.h"

/*
**	Initialisation of each variable for the raycast
*/

t_ray_cast	*init_rc(t_ray_cast *all, int x)
{
	if (x == 0)
		all->cam_plane = init_ptd(0, 0.66);
	all->cam_x = 2 * x / (double)WIN_WIDTH - 1;
	all->ray_dir.x = all->play_vec.x + all->cam_plane.x * all->cam_x;
	all->ray_dir.y = all->play_vec.y + all->cam_plane.y * all->cam_x;
	all->map_co.x = (int)all->play_pos.x;
	all->map_co.y = (int)all->play_pos.y;
	all->delta_dist.x = double_abs(1 / all->ray_dir.x);
	all->delta_dist.y = double_abs(1 / all->ray_dir.y);
	return (all);
}

/*
**	Calc the distance between the ray starting position and the first side with 
**	the diretion of the ray casted
*/

t_ray_cast	*calc_step(t_ray_cast *all)
{
	if (all->ray_dir.x < 0)
	{
		all->step.x = -1;
		all->len_next_side.x = (all->play_pos.x - all->map_co.x) * all->delta_dist.x;
	}
	else
	{
		all->step.x = 1;
		all->len_next_side.x =\
						(all->map_co.x + 1.0 - all->play_pos.x) * all->delta_dist.x;
	}
	if (all->ray_dir.y < 0)
	{
		all->step.y = -1;
		all->len_next_side.y = (all->play_pos.y - all->map_co.y) * all->delta_dist.y;
	}
	else
	{
		all->step.y = 1;
		all->len_next_side.y =\
						(all->map_co.y + 1.0 - all->play_pos.y) * all->delta_dist.y;
	}
	return (all);
}

/*
** 	Digital Differential Analizer Algorithm | Jump one square each loop while 
**	a wall isn't hit
*/

t_ray_cast	*dda(int map[4][10], t_ray_cast *all)
{
	int		hit;

	all->wall_side = 0;
	hit = 0;
	while (hit == 0)
	{
		if (all->len_next_side.x < all->len_next_side.y)
		{
			all->len_next_side.x += all->delta_dist.x;
			all->map_co.x += all->step.x;
			all->wall_side = 0;
		}
		else
		{
			all->len_next_side.y += all->delta_dist.y;
			all->map_co.y += all->step.y;
			all->wall_side = 1;
		}
		if (map[(int)all->map_co.x][(int)all->map_co.y] > 0)
			hit = 1;
	}
	return (all);
}

/*
**	Calculate the height of the line to be drawn and draw the line
*/

t_ray_cast	*draw(t_ray_cast *all, SDL_Renderer *ren, int map[4][10], int x)
{
	all->line_height = (int)(WIN_HEIGHT / all->wall_dist);
	all->line_draw.x = -all->line_height / 2 + WIN_HEIGHT / 2;
	all->line_draw.y = all->line_height / 2 + WIN_HEIGHT / 2;
	if (all->line_draw.x < 0)
		all->line_draw.x = 0;
	if (all->line_draw.y > WIN_HEIGHT)
		all->line_draw.y = WIN_HEIGHT - 1;
	check_wall_color(ren, map[(int)all->map_co.x][(int)all->map_co.y], all->wall_side);
	//SDL_RenderDrawLine(ren, x, all.line_draw.x, x, all.line_draw.y);		
	draw_line(init_ptd(x, all->line_draw.x), init_ptd(x, all->line_draw.y), ren);
	return (all);
}

/*
**	Beginning of Raycasting Algorithm | Each iteration is for a vertical stripe
*/

t_ray_cast	*raycast(SDL_Renderer *ren, int map[4][10], int start, t_ray_cast *all)
{
	int			x;

	x = -1;
	if (start == 1)
	{
		all->play_pos = init_ptd(2.0, 2.0);
		all->play_vec = init_ptd(0, 1);
	}
	while (++x < WIN_WIDTH)
	{
		all = init_rc(all, x);
		all = calc_step(all);
		all = dda(map, all);
		if (all->wall_side == 0)
			all->wall_dist = (all->map_co.x - all->play_pos.x + (1 - all->step.x) / 2)\
							/ all->ray_dir.x;
		else
			all->wall_dist = (all->map_co.y - all->play_pos.y + (1 - all->step.y) / 2)\
							/ all->ray_dir.y;
	printf("oui\n");		
		all = draw(all, ren, map, x);
	}
	return (all);
}