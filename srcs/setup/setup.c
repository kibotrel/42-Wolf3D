/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 17:17:25 by kibotrel          #+#    #+#             */
/*   Updated: 2019/05/28 10:34:42 by nde-jesu         ###   ########.fr       */
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
	sdl->win = SDL_CreateWindow("Wolf3D", 0, 0, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
	sdl->ren = SDL_CreateRenderer(sdl->win, -1, SDL_RENDERER_TARGETTEXTURE);
		//ERRORS
	sdl->text = SDL_CreateTexture(sdl->ren, ARGB, STREAM, WIDTH, HEIGHT);
	if (!(sdl->pixels = (uint32_t*)malloc(4 * ((WIDTH + 1) * HEIGHT))))
		return ;
	sdl->surf[0] = SDL_LoadBMP("01.bmp");
	sdl->surf[1] = SDL_LoadBMP("05.bmp");
	sdl->surf[2] = SDL_LoadBMP("13.bmp");
	sdl->surf[3] = SDL_LoadBMP("23.bmp");
	SDL_WarpMouseInWindow(sdl->win, WIDTH / 2, HEIGHT / 2);
	SDL_ShowCursor(SDL_DISABLE);
}

void		cam_setup(t_cam *cam)
{
	cam->pos.x = 1.5;
	cam->pos.y = 3.5;
	cam->coord.x = cam->pos.x * CELL;
	cam->coord.y = cam->pos.y * CELL;
	cam->angle = to_rad(315);
	cam->height = 0;
}

void		setup_raycasting(t_cam *cam, t_ray *ray)
{
	if (cam->angle >= to_rad(330))
		ray->angle = cam->angle - to_rad(330);
	else
		ray->angle = cam->angle + to_rad(30);
}

void		setup(t_env *env)
{
	sdl_setup(&env->sdl);
	cam_setup(&env->cam);
	env->ray.screen = ((WIDTH / 2) / tan(to_rad(30)));
	env->w = WIDTH;
	env->h = HEIGHT;
}

void		setup_mouse(t_mouse *mouse, t_env *env)
{
	mouse->new.x = env->w / 2;
	mouse->new.y = env->h / 2;
	mouse->old.x = env->w / 2;
	mouse->old.y = env->h / 2;
	mouse->toggle_mouse = 1;
	mouse->old_time = 0;
}
