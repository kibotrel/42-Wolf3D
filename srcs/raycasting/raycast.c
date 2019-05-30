/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:30:34 by nde-jesu          #+#    #+#             */
/*   Updated: 2019/05/30 15:10:49 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "env.h"
#include "wolf3d.h"

static void	draw_slice(t_wall wall, t_sdl *sdl)
{
	int		color;
	t_pos	current;

	current.x = wall.start.x;
	current.y = -1;
	while (++current.y < HEIGHT)
	{
		if (current.y < wall.start.y)
			color = SKY;
		else if (current.y >= wall.start.y && current.y <= wall.end.y)
			color = wall.color;
		else
			color = FLOOR;
		sdl->pixels[(int)(current.x + (current.y * (WIDTH)))] = color;
	}
}

void		raycast(t_env *env, t_sdl *sdl, t_ray *ray)
{
	int		x;
	x = -1;
	setup_raycasting(&env->cam, &env->ray);
	while (++x < WIDTH)
	{
		y_collisions(ray, env->cam);
		x_collisions(ray, env->cam, env->data);
		check_collisions(ray, env->map, env->height, env->width);
		setup_slice(ray, &env->cam, x, env);
		draw_slice(ray->wall, sdl);
		ray->angle -= ray->step;
		if (env->ray.angle >= env->data.two_pi)
			env->ray.angle -= env->data.two_pi;
	}
	if (SDL_UpdateTexture(sdl->text, 0, sdl->pixels, WIDTH * 4) < 0)
		free_sdl(env, 5, ERR_UPDATE, 17);
	if (SDL_RenderCopy(sdl->ren, sdl->text, 0, 0) < 0)
		free_sdl(env, 5, ERR_COPY, 18);
	SDL_RenderPresent(sdl->ren);
}
