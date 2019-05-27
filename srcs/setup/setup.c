/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 17:17:25 by kibotrel          #+#    #+#             */
/*   Updated: 2019/05/27 16:52:06 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "SDL.h"
#include "env.h"
#include "wolf3d.h"

static void	sdl_setup(t_sdl *sdl)
{
	SDL_Init(SDL_INIT_VIDEO);
		//ERROR
	sdl->win = SDL_CreateWindow("Wolf3D", 0, 0, WIDTH, HEIGHT, RESIZE);
		//ERROR
	sdl->render = SDL_CreateRenderer(sdl->win, -1, SDL_RENDERER_TARGETTEXTURE);
		//ERROR
	sdl->texture = SDL_CreateTexture(sdl->render, ARGB, STREAM, WIDTH, HEIGHT);
		//ERROR
	if (!(sdl->pixels = (uint32_t*)malloc(4 * ((WIDTH + 1) * HEIGHT))))
		return ;
	SDL_WarpMouseInWindow(sdl->win, WIDTH / 2, HEIGHT / 2);
		//ERROR
	SDL_ShowCursor(SDL_DISABLE);
		//ERROR
}

void		cam_setup(t_cam *cam)
{
	cam->pos.x = 1.5;
	cam->pos.y = 3.5;
	cam->coord.x = cam->pos.x * CELL;
	cam->coord.y = cam->pos.y * CELL;
	cam->angle = radians(315);
	cam->height = 0;
	cam->fov = 60.0;
}

void		setup_raycasting(t_cam *cam, t_ray *ray)
{
	if (cam->angle >= 330)
		ray->angle = cam->angle - radians(330);
	else
		ray->angle = cam->angle + radians(30);
	ray->step = radians(cam->fov / WIDTH);
}

void		setup(t_env *env)
{
	sdl_setup(&env->sdl);
	cam_setup(&env->cam);
	env->ray.screen = ((WIDTH / 2) / tan(radians(env->cam.fov / 2)));
}
