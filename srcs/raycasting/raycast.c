/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:30:34 by nde-jesu          #+#    #+#             */
/*   Updated: 2019/06/07 13:21:43 by reda-con         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "env.h"
#include "wolf3d.h"

static int	get_color(SDL_Surface *surf, int x, int y)
{
	uint8_t		*p;
	t_color		clr;

	p = surf->pixels + y * surf->pitch - x * surf->format->BytesPerPixel;
	SDL_GetRGB(*p, surf->format, &clr.r, &clr.g, &clr.b);
	return (clr.r << 16 | clr.g << 8 | clr.b);
}

void		draw_slice(t_pos start, t_pos end, t_env *env, t_ray *ray)
{
	t_pos		current;
	int			color;
	int			i;
	int			tex;

	current.x = start.x;
	current.y = -1;
	while (++current.y < env->h)
	{
		if (current.y <= start.y)
			color = 0xff00ffff;
		else if (current.y > start.y && current.y < end.y)
		{
			i = (current.y - env->cam.offset) * 256 - (env->h) * 128\
				+ ray->wall.size * 128;
			tex = i * CELL / ray->wall.size / 256 + 1;
			color = get_color(env->sdl.surf[ray->which_wall], ray->offset, tex);
		}
		else
			color = 0xffc8c8c8;
		env->sdl.pixels[(int)(current.x + (current.y * (env->w)))] = color;
	}
}

void		raycast(t_env *env, t_ray *ray)
{
	int		x;

	x = -1;
	setup_raycasting(&env->cam, &env->ray, env->w);
	while (++x < env->w)
	{
		y_collisions(ray, env->cam);
		x_collisions(ray, env->cam, env->data);
		check_collisions(ray, env->map, env->height, env->width);
		setup_slice(ray, &env->cam, x, env);
		draw_slice(ray->wall.start, ray->wall.end, env, ray);
		ray->angle -= ray->step;
		if (env->ray.angle >= env->data.two_pi)
			env->ray.angle -= env->data.two_pi;
	}
}
