/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:30:34 by nde-jesu          #+#    #+#             */
/*   Updated: 2019/05/31 12:09:20 by reda-con         ###   ########.fr       */
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

static void		setup_line(t_env *env, t_ray *ray, t_cam *cam, int x)
{
	double	angle;

	angle = cam->angle - ray->angle;
	ray->dist = length(ray->hit_x, ray->hit_y, cam->coord, ray) * cos(angle);
	ray->wall.size = ceil((CELL / ray->dist) * ray->screen);
	ray->wall.start.x = x;
	ray->wall.start.y = ((env->h / 2) - (ray->wall.size / 2)) + cam->height;
	ray->wall.end.x = x;
	ray->wall.end.y = ray->wall.start.y + ray->wall.size;
}

void			raycast(int **map, t_env *env, t_cam *cam, t_ray *ray)
{
	int		x;

	x = -1;
	setup_raycasting(cam, ray);
	while (++x < env->w)
	{
		y_collisions(&ray->hit_y, &ray->gap_y, ray->angle, *cam);
		x_collisions(&ray->hit_x, &ray->gap_x, ray->angle, *cam);
		check_collisions(ray, map, env->height, env->width);
		setup_line(env, ray, cam, x);
		draw_rc(ray->wall.start, ray->wall.end, env, ray);
		ray->angle -= (to_rad(60.0) / WIDTH);
		if (ray->angle >= 6.283185)
			ray->angle -= 6.283185;
	}
	SDL_UpdateTexture(env->sdl.text, NULL, env->sdl.pixels, env->w * S_UINT);
	SDL_RenderCopy(env->sdl.ren, env->sdl.text, NULL, NULL);
	SDL_RenderPresent(env->sdl.ren);
}
