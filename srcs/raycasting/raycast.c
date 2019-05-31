/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:30:34 by nde-jesu          #+#    #+#             */
/*   Updated: 2019/05/31 14:32:43 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "env.h"
#include "wolf3d.h"

static int	get_pixel_surface(SDL_Surface *surf, int x, int y)
{
	uint8_t	*p;

	p = surf->pixels + y * surf->pitch - x * surf->format->BytesPerPixel;
	return (*p);
}

static void	draw_slice(t_pos start, t_pos end, t_env *env, t_ray *ray)
{
	t_pos		current;
	int			color;
	t_color		clr;

	current.x = start.x;
	current.y = -1;
	while (++current.y < env->h)
	{
		if (current.y < start.y)
			color = SKY;
		else if (current.y >= start.y && current.y <= end.y)
		{
			SDL_GetRGB(get_pixel_surface(env->sdl.surf[ray->which_wall],
				ray->offset, (int)current.y % CELL),
				env->sdl.surf[ray->which_wall]->format, &clr.r, &clr.g, &clr.b);
			color = clr.r << 16 | clr.g << 8 | clr.b;
		}
		else
			color = FLOOR;
		env->sdl.pixels[(int)(current.x + (current.y * (env->w)))] = color;
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
		draw_slice(ray->wall.start, ray->wall.end, env, ray);
		ray->angle -= ray->step;
		if (env->ray.angle >= env->data.two_pi)
			env->ray.angle -= env->data.two_pi;
	}
	hud(env);
	if (SDL_UpdateTexture(sdl->text, 0, sdl->pixels, WIDTH * 4) < 0)
		free_sdl(env, 5, ERR_UPDATE, 17);
	if (SDL_RenderCopy(sdl->ren, sdl->text, 0, 0) < 0)
		free_sdl(env, 5, ERR_COPY, 18);
	SDL_RenderPresent(sdl->ren);
}
