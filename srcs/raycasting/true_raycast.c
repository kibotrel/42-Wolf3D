/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   true_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:30:34 by nde-jesu          #+#    #+#             */
/*   Updated: 2019/05/13 18:29:58 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "env.h"
#include "wolf3d.h"

static void	check_bounds(t_ray *ray)
{
	ray->hit_y.x = (ray->hit_y.x < 0) ? 0 : ray->hit_y.x;
	ray->hit_y.y = (ray->hit_y.y < 0) ? 0 : ray->hit_y.y;
	ray->hit_x.x = (ray->hit_x.x < 0) ? 0 : ray->hit_x.x;
	ray->hit_x.y = (ray->hit_x.y < 0) ? 0 : ray->hit_x.y;
	ray->hit_y.x = (ray->hit_y.x > 6 * CELL) ? 6 * CELL : ray->hit_y.x;
	ray->hit_y.y = (ray->hit_y.y > 6 * CELL) ? 6 * CELL : ray->hit_y.y;
	ray->hit_x.x = (ray->hit_x.x > 6 * CELL) ? 6 * CELL : ray->hit_x.x;
	ray->hit_x.y = (ray->hit_x.y > 6 * CELL) ? 6 * CELL : ray->hit_x.y;
}

static void	check_collisions(t_ray *rc, int **map)
{
	t_pos	hit;

	hit.x = 0;
	hit.y = 0;
	while (hit.x == 0 || hit.y == 0)
	{
		check_bounds(rc);
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

void		raycast(int **map, t_sdl *sdl, t_cam *cam, t_ray *ray)
{
	int		x;

	x = -1;
	setup_raycasting(cam, ray);
	while (++x < WIDTH)
	{
		y_collisions(&ray->hit_y, &ray->gap_y, ray->angle, *cam);
		x_collisions(&ray->hit_x, &ray->gap_x, ray->angle, *cam);
		check_collisions(ray, map);
		setup_line(ray, cam, x);
		draw_rc(ray->wall.start, ray->wall.end, sdl->ren, DARK_GRAY);
		ray->angle += (60.0 * RADIAN) / WIDTH;
	}
	SDL_RenderPresent(sdl->ren);
}
