/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:30:34 by nde-jesu          #+#    #+#             */
/*   Updated: 2019/06/27 17:00:27 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "env.h"
#include "wolf3d.h"

static int		get_color(t_png surf, int x, int y)
{
	if (surf.pixels)
		return (surf.pixels[x + y * surf.width]);
	else
		return (0);
}

static unsigned int		draw_wall(t_pos str, t_pos end, t_env *env, t_pos *cur)
{
	int				i;
	int				tex;
	unsigned int	color;

	if (env->tex_on == 1)
	{
		i = (cur->y - env->cam.offset) * 256 - (env->h) * 128 + env->ray.wall.size * 128;
		tex = (i * CELL / env->ray.wall.size / 256);
		color = get_color(env->sdl.surf[env->ray.which_wall],
				env->ray.offset, tex);
	}
	else
	{
		if (cur->y <= str.y + 11 || cur->y >= end.y - 11\
				|| env->ray.offset < 1 || env->ray.offset > 62)
			color = 0x000000;
		else
			color = env->sdl.colors[env->ray.which_wall];
	}
	return (color);
}

static void		draw_slice(t_pos start, t_pos end, t_env *env)
{
	t_pos			current;
	unsigned int	color;

	current.x = start.x;
	current.y = -1;
	while (++current.y < env->h)
	{
		if (current.y <= start.y)
			color = 0xbddcfc;
		else if (current.y > start.y && current.y < end.y)
			color = draw_wall(start, end, env, &current);
		else
			color = FLOOR_HITLER;
		env->sdl.pixels[(int)(current.x + (current.y * (env->w)))] = color;
	}
}

void			raycast(t_env *env, t_ray *ray)
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
		draw_slice(ray->wall.start, ray->wall.end, env);
		ray->angle -= ray->step;
		if (env->ray.angle >= env->data.two_pi)
			env->ray.angle -= env->data.two_pi;
	}
}
