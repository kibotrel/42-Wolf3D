/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 13:14:59 by reda-con          #+#    #+#             */
/*   Updated: 2019/05/29 10:16:13 by nde-jesu         ###   ########.fr       */
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

static int	get_pixel_surface(SDL_Surface *surf, int x, int y)
{
	uint8_t	*p;

	p = surf->pixels + y * surf->pitch - x * surf->format->BytesPerPixel;
	return (*p);
}
#include <stdio.h>
void			draw_rc(t_pos start, t_pos end, t_env *env, t_ray *ray)
{
	t_pos		current;
	int			color;
	t_color		clr;
	int			wall_unit;
	int			j;
	int			i;

	current.x = start.x;
	current.y = -1;
	wall_unit = (int)ray->wall.size / CELL;
	i = wall_unit;
	j = 0;
	// printf("%i %f %f\n",(int)ray->wall.size, wall_unit, wall_unit * 64);
	while (++current.y < env->h)
	{
		if (current.y < start.y)
			color = 0xff00ffff;
		else if (current.y >= start.y && current.y < end.y)
		{
			if (i == wall_unit && j < 64)
			{
				i = -1;
				color = get_pixel_surface(env->sdl.surf[ray->which_wall],
					ray->offset, j);
				SDL_GetRGB(color,env->sdl.surf[ray->which_wall]->format, &clr.r, 
					&clr.g, &clr.b);
				color = clr.r << 16 | clr.g << 8 | clr.b;
				++j;
			}
			++i;
			if (ray->offset == 0 || ray->offset == 	63)
				color = 0xffffffff;
		}
		else
			color = 0xffc8c8c8;
		env->sdl.pixels[(int)(current.x + (current.y * (env->w)))] = color;
	}
	// exit(1);
}
