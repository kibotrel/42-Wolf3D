/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 13:14:59 by reda-con          #+#    #+#             */
/*   Updated: 2019/05/14 15:08:18 by nde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "env.h"
#include <math.h>

void		fun_exit(SDL_Renderer *ren, SDL_Window *win)
{
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	exit(0);
}

double	double_abs(double i)
{
	return ((i > 0) ? i : -i);
}

#include <unistd.h>
#include <stdio.h>
void		draw_rc(t_pos start, t_pos end, t_sdl sdl, int clr)
{
	t_pos	current;
	int		color;

	current.x = start.x;
	current.y = 0;
	while (current.y < HEIGHT)
	{
		if (current.y < start.y)
			color = 0x00ffffff;
		else if (current.y >= start.y && current.y <= end.y)
			color = clr;
		else
			color = 0xc8c8c8ff;
		sdl.pixels[(int)(current.x + (current.y * (WIDTH)))] = color;
		++current.y;
	}
}

double		length(t_pos col_x, t_pos col_y, t_pos play_coor)
{
	double	is_y;
	double	is_x;

	is_x = sqrt(pow(col_x.x - play_coor.x, 2) + pow(col_x.y - play_coor.y, 2));
	is_y = sqrt(pow(col_y.x - play_coor.x, 2) + pow(col_y.y - play_coor.y, 2));
	return (is_x > is_y ? is_y : is_x);
}
