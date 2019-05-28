/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 13:14:59 by reda-con          #+#    #+#             */
/*   Updated: 2019/05/28 09:40:07 by nde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "env.h"
#include <math.h>

void			fun_exit(SDL_Renderer *ren, SDL_Window *win)
{
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	exit(0);
}

static uint32_t	get_pixel_surface(SDL_Surface *surf, int x, int y)
{
    uint8_t        *p;
    
    p = surf->pixels + y * surf->pitch + x * surf->format->BytesPerPixel;
    return (*p);
}
#include <stdio.h>
void			draw_rc(t_pos start, t_pos end, t_env *env, t_ray *ray)
{
	t_pos		current;
	uint32_t	color;

	current.x = start.x;
	current.y = 0;
	while (current.y < env->h)
	{
		if (current.y < start.y)
			color = 0xff00ffff;
		else if (current.y >= start.y && current.y <= end.y)
				color = get_pixel_surface(env->sdl.surf[ray->what_wall], (int)current.x % CELL, (int)current.y % CELL);
		else
			color = 0xffc8c8c8;
		env->sdl.pixels[(int)(current.x + (current.y * (env->w)))] = color;
		++current.y;
	}
}
