/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 13:14:59 by reda-con          #+#    #+#             */
/*   Updated: 2019/05/28 19:08:08 by reda-con         ###   ########.fr       */
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
//	printf("0x%0x\n", *p);
	return (*p);
}

void			draw_rc(t_pos start, t_pos end, t_env *env, t_ray *ray)
{
	t_pos		current;
	int			color;
	int			unit_size;
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;

	r = 0;
	g = 0;
	b = 0;
	current.x = start.x;
	current.y = 0;
	unit_size = (int)ray->wall.size % CELL;
	while (current.y < env->h)
	{
		if (current.y < start.y)
			color = 0xff00ffff;
		else if (current.y >= start.y && current.y <= end.y)
		{
			SDL_GetRGB(get_pixel_surface(env->sdl.surf[ray->which_wall], ray->offset, (int)current.y % CELL)
				, env->sdl.surf[ray->which_wall]->format, &r, &g, &b);
			//color = get_pixel_surface(env->sdl.surf[ray->which_wall], ray->offset, (int)current.y % CELL);
			color = r << 16 | g << 8 | b;
		}
		else
			color = 0xffc8c8c8;
		env->sdl.pixels[(int)(current.x + (current.y * (env->w)))] = color;
		++current.y;
	}
}
