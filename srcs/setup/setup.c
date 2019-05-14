/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 17:17:25 by kibotrel          #+#    #+#             */
/*   Updated: 2019/05/14 09:14:08 by nde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "SDL.h"
#include "env.h"
#include "wolf3d.h"


static void	sdl_setup(t_sdl *sdl)
{
	SDL_Init(SDL_INIT_VIDEO);
		//ERROR
	SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, RESIZE, &sdl->win, &sdl->ren);
		//ERROR
}

static void	cam_setup(t_cam *cam)
{
	cam->pos.x = 4.5;
	cam->pos.y = 4.5;
	cam->coord.x = cam->pos.x * CELL + (cam->pos.x - cam->pos.x) * CELL;
	cam->coord.y = cam->pos.y * CELL + (cam->pos.y - cam->pos.y) * CELL;
	cam->angle = 90 * RADIAN;
}

void		setup_raycasting(t_cam *cam, t_ray *ray)
{
	if (cam->angle < 30 * RADIAN)
		ray->angle = cam->angle + (330 * RADIAN);
	else
		ray->angle = cam->angle - (30 * RADIAN);
}

void		setup(t_env *env)
{
	sdl_setup(&env->sdl);
	cam_setup(&env->cam);
	env->ray.screen = (WIDTH / 2) / tan(30 * RADIAN);
}
