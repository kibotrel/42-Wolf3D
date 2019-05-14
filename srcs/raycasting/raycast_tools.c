/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reda-con <reda-con@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 13:14:59 by reda-con          #+#    #+#             */
/*   Updated: 2019/05/14 10:51:27 by reda-con         ###   ########.fr       */
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

void		draw_rc(t_pos start, t_pos end, SDL_Renderer *ren, int clr)
{
	t_pos	current;

	current.x = start.x;
	current.y = 0;
	while (current.y < HEIGHT)
	{
		if (current.y < start.y)
			SDL_SetRenderDrawColor(ren, 0, 255, 255, 255);
		else if (current.y >= start.y && current.y <= end.y)
			SDL_SetRenderDrawColor(ren, clr >> 16, clr >> 8, clr, 255);
		else
			SDL_SetRenderDrawColor(ren, 200, 200, 200, 255);
		SDL_RenderDrawPoint(ren, (int)current.x, (int)current.y);
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
