/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 17:17:25 by kibotrel          #+#    #+#             */
/*   Updated: 2019/05/10 18:56:52 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "SDL.h"
#include "wolf3d.h"


static void	sdl_setup(t_sdl *sdl)
{
	SDL_Init(SDL_INIT_VIDEO);
		//ERROR
	SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, RESIZE, &sdl->win, &sdl->ren);
		//ERROR
}

static void	player_setup(t_player *p)
{
	p->play_pos.x = 2.5;
	p->play_pos.y = 2.5;
	p->play_coor.x = (int)p->play_pos.x * SQUARE_SIZE + (p->play_pos.x - (int)p->play_pos.x) * SQUARE_SIZE;
	p->play_coor.y = (int)p->play_pos.y * SQUARE_SIZE + (p->play_pos.y - (int)p->play_pos.y) * SQUARE_SIZE;
	p->play_angle = 135 * RADIAN;

}

void		setup_raycasting(t_player *play, t_ray_cast *all)
{
	if (play->play_angle < 30 * RADIAN)
		all->act_angle = play->play_angle + (330 * RADIAN);
	else
		all->act_angle = play->play_angle - (30 * RADIAN);
}

void		setup(t_env *env);
{
	sdl_setup(env->sdl);
	player_setup(env->player);
}
