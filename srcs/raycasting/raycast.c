/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:30:34 by nde-jesu          #+#    #+#             */
/*   Updated: 2019/05/27 16:51:06 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "env.h"
#include "wolf3d.h"

static void		check_bounds(double *x, double *y, int max_x, int max_y)
{
	if (*x > (max_x - 1) * CELL)
		*x = (max_x - 1) * CELL;
	else if (*x < 0)
		*x = 0;
	if (*y > (max_y - 1) * CELL)
		*y = (max_y - 1) * CELL;
	else if (*y < 0)
		*y = 0;
}

static void		check_collisions(t_ray *rc, int **map, int max_y, int max_x)
{
	t_pos	hit;

	hit.x = 0;
	hit.y = 0;
	while (hit.x == 0 || hit.y == 0)
	{
		if (hit.x == 0)
			check_bounds(&rc->hit_x.x, &rc->hit_x.y, max_x, max_y);
		if (hit.y == 0)
			check_bounds(&rc->hit_y.x, &rc->hit_y.y, max_x, max_y);
		if (map[(int)rc->hit_x.y / CELL][(int)rc->hit_x.x / CELL])
			hit.x = 1;
		else if (hit.x == 0)
		{
			rc->hit_x.x += rc->gap_x.x;
			rc->hit_x.y += rc->gap_x.y;
		}
		if (map[(int)rc->hit_y.y / CELL][(int)rc->hit_y.x / CELL])
			hit.y = 1;
		else if (hit.y == 0)
		{
			rc->hit_y.x += rc->gap_y.x;
			rc->hit_y.y += rc->gap_y.y;
		}
	}
}

static void		setup_line(t_ray *ray, t_cam *cam, int x)
{
	double	angle;

	angle = cam->angle - ray->angle;
	ray->dist = length(ray->hit_x, ray->hit_y, cam->coord, ray) * cos(angle);
	ray->wall.size = ceil((CELL / ray->dist) * ray->screen - cam->height);
	ray->wall.start.x = x;
	ray->wall.start.y = ((HEIGHT / 2) - (ray->wall.size / 2)) + cam->height;
	ray->wall.end.x = x;
	ray->wall.end.y = (ray->wall.start.y + ray->wall.size) + cam->height;
}

void			raycast(t_env *env)
{
	int		x;

	x = -1;
	setup_raycasting(&env->cam, &env->ray);
	while (++x < WIDTH)
	{
		y_collisions(&env->ray.hit_y, &env->ray.gap_y, env->ray.angle, env->cam);
		x_collisions(&env->ray.hit_x, &env->ray.gap_x, env->ray.angle, env->cam);
		check_collisions(&env->ray, env->map, env->height, env->width);
		setup_line(&env->ray, &env->cam, x);
		draw_rc(env->ray.wall.start, env->ray.wall.end, env->sdl, env->ray.wall.color);
		env->ray.angle -= env->ray.step;
		if (env->ray.angle >= 6.283185)
			env->ray.angle -= 6.283185;
	}
	SDL_UpdateTexture(env->sdl.texture, NULL, env->sdl.pixels, WIDTH * S_UINT);
	SDL_RenderCopy(env->sdl.render, env->sdl.texture, NULL, NULL);
	SDL_RenderPresent(env->sdl.render);
}
