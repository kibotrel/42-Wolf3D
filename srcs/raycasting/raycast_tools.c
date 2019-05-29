/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 13:14:59 by reda-con          #+#    #+#             */
/*   Updated: 2019/05/29 19:04:25 by reda-con         ###   ########.fr       */
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

static int	get_color(SDL_Surface *surf, int x, int y)
{
	uint8_t	*p;
	t_color		clr;

	p = surf->pixels + y * surf->pitch - x * surf->format->BytesPerPixel;
	SDL_GetRGB(*p, surf->format, &clr.r, &clr.g, &clr.b);
	return (clr.r << 16 | clr.g << 8 | clr.b);
}

#include <stdio.h>
void			draw_rc(t_pos start, t_pos end, t_env *env, t_ray *ray)
{
	t_pos		current;
	int			color;
	double		i;
	int			j;
	double		unit;

	current.x = start.x;
	current.y = -1;
	j = 1;
	unit = ray->wall.size / CELL;
	i = unit;
	while (++current.y < env->h)
	{
		if (current.y < start.y)
			color = 0xff00ffff;
		else if (current.y >= start.y && current.y < end.y)
		{
			if (i <= unit && j <= CELL)
			{
				i = -unit;
				color = get_color(env->sdl.surf[ray->which_wall],
					ray->offset + 1, j);
				++j;
			}
			i += 1;
		}
		else
			color = 0xffc8c8c8;
		env->sdl.pixels[(int)(current.x + (current.y * (env->w)))] = color;
	}
}
