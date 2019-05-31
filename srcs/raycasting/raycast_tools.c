/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 13:14:59 by reda-con          #+#    #+#             */
/*   Updated: 2019/05/31 12:05:17 by reda-con         ###   ########.fr       */
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
	int			i;
	int			tex_y;

	current.x = start.x;
	current.y = -1;
	while (++current.y < env->h)
	{
		if (current.y <= start.y)
			color = 0xff00ffff;
		else if (current.y > start.y && current.y < end.y)
		{
			i = (current.y -env->cam.height) * 256 - env->h * 128 + ray->wall.size * 128;
			tex_y = i * CELL / ray->wall.size / 256;
			color = get_color(env->sdl.surf[ray->which_wall], ray->offset + 1, tex_y + 1);
		}
		else
			color = 0xffc8c8c8;
		env->sdl.pixels[(int)(current.x + (current.y * (env->w)))] = color;
	}
}
