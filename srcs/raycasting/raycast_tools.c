/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reda-con <reda-con@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 13:14:59 by reda-con          #+#    #+#             */
/*   Updated: 2019/05/23 10:51:54 by reda-con         ###   ########.fr       */
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

void		draw_rc(t_pos start, t_pos end, t_sdl sdl, int clr)
{
	t_pos	current;
	int		color;

	current.x = start.x;
	current.y = 0;
	while (current.y < HEIGHT)
	{
		if (current.y < start.y)
			color = 0xff00ffff;
		else if (current.y >= start.y && current.y <= end.y)
			color = clr;
		else
			color = 0xffc8c8c8;
		sdl.pixels[(int)(current.x + (current.y * (WIDTH)))] = color;
		++current.y;
	}
}
