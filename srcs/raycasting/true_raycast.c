/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   true_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:30:34 by nde-jesu          #+#    #+#             */
/*   Updated: 2019/05/14 10:26:33 by reda-con         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "env.h"
#include "wolf3d.h"

static void	check_bounds(t_ray *ray, int max_x, int max_y)
{
	ray->hit_y.x = (ray->hit_y.x < 0) ? 0 : ray->hit_y.x;
	ray->hit_y.y = (ray->hit_y.y < 0) ? 0 : ray->hit_y.y;
	ray->hit_x.x = (ray->hit_x.x < 0) ? 0 : ray->hit_x.x;
	ray->hit_x.y = (ray->hit_x.y < 0) ? 0 : ray->hit_x.y;
	ray->hit_y.x = (ray->hit_y.x > max_x * CELL) ? max_x * CELL : ray->hit_y.x;
	ray->hit_y.y = (ray->hit_y.y > max_y * CELL) ? max_y * CELL : ray->hit_y.y;
	ray->hit_x.x = (ray->hit_x.x > max_x * CELL) ? max_x * CELL : ray->hit_x.x;
	ray->hit_x.y = (ray->hit_x.y > max_y * CELL) ? max_y * CELL : ray->hit_x.y;
}

static void	check_collisions(t_ray *rc, int **map, int max_y, int max_x)
{
	t_pos	hit;

	hit.x = 0;
	hit.y = 0;
	while (hit.x == 0 || hit.y == 0)
	{
		check_bounds(rc, max_x, max_y);
		if (hit.x == 0 && map[(int)rc->hit_x.y / CELL][(int)rc->hit_x.x / CELL])
			hit.x = 1;
		else if (hit.x == 0)
		{
			rc->hit_x.x += rc->gap_x.x;
			rc->hit_x.y += rc->gap_x.y;
		}
		if (hit.y == 0 && map[(int)rc->hit_y.y / CELL][(int)rc->hit_y.x / CELL])
			hit.y = 1;
		else if (hit.y == 0)
		{
			rc->hit_y.x += rc->gap_y.x;
			rc->hit_y.y += rc->gap_y.y;
		}
	}
}

static void	setup_line(t_ray *ray, t_cam *cam, int x)
{
	ray->dist = length(ray->hit_x, ray->hit_y, cam->coord);
	ray->dist *= cos(cam->angle - ray->angle);
	ray->wall.size = ceil((CELL / ray->dist) * ray->screen);
	ray->wall.start.x = WIDTH - x;
	ray->wall.start.y = (HEIGHT / 2) - (ray->wall.size / 2);
	ray->wall.end.x = WIDTH - x;
	ray->wall.end.y = ray->wall.start.y + ray->wall.size;
}

void		raycast(int **map, t_env *env, t_cam *cam, t_ray *ray)
{
	int		x;

	x = -1;
	setup_raycasting(cam, ray);
	while (++x < WIDTH)
	{
		y_collisions(&ray->hit_y, &ray->gap_y, ray->angle, *cam);
		x_collisions(&ray->hit_x, &ray->gap_x, ray->angle, *cam);
		check_collisions(ray, map, env->height, env->width);
		setup_line(ray, cam, x);
		draw_rc(ray->wall.start, ray->wall.end, env->sdl.ren, DARK_GRAY);
		ray->angle += (60.0 * RADIAN) / WIDTH;
	}
	SDL_RenderPresent(env->sdl.ren);
}
