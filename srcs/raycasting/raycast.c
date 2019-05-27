/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:30:34 by nde-jesu          #+#    #+#             */
/*   Updated: 2019/05/27 19:19:31 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "env.h"
#include "wolf3d.h"

static void		setup_line(t_ray *ray, t_cam *cam, int x, t_env *env)
{
	double	angle;

	angle = cam->angle - ray->angle;
	ray->dist = length(ray->hit_x, ray->hit_y, cam->coord, env) * cos(angle);
	ray->wall.size = ceil((CELL / ray->dist) * ray->screen);
	ray->wall.start.x = x;
	ray->wall.start.y = cam->offset - (ray->wall.size / 2);
	ray->wall.end.x = x;
	ray->wall.end.y = (ray->wall.start.y + ray->wall.size);
}

static void		setup_raycasting(t_cam *cam, t_ray *ray)
{
	if (cam->angle >= radians(330))
		ray->angle = cam->angle - radians(330);
	else
		ray->angle = cam->angle + radians(30);
	ray->step = radians(cam->fov / WIDTH);
}

void			raycast(t_env *env)
{
	int		x;

	x = -1;
	setup_raycasting(&env->cam, &env->ray);
	while (++x < WIDTH)
	{
		y_collisions(&env->ray, env->cam, env->data);
		x_collisions(&env->ray, env->cam, env->data);
		check_collisions(&env->ray, env->map, env->height, env->width);
		setup_line(&env->ray, &env->cam, x, env);
		draw_rc(env->ray.wall.start, env->ray.wall.end, env->sdl, env->ray.wall.color);
		env->ray.angle -= env->ray.step;
		if (env->ray.angle >= env->data.two_pi)
			env->ray.angle -= env->data.two_pi;
	}
	SDL_UpdateTexture(env->sdl.texture, NULL, env->sdl.pixels, WIDTH * S_UINT);
	SDL_RenderCopy(env->sdl.render, env->sdl.texture, NULL, NULL);
	SDL_RenderPresent(env->sdl.render);
}
