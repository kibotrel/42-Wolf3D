/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 09:28:35 by nde-jesu          #+#    #+#             */
/*   Updated: 2019/04/29 11:09:59 by nde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "SDL.h"
#include "wolf3d.h"

#define SPEED 0.5

#include <stdio.h>
void		control(t_ray_cast *all, int worldMap[4][10], SDL_Window *win, SDL_Renderer *ren)
{
	SDL_Event 	ev;
	int			make;
	double		old_play_vec_x;
	double		old_cam_plane_x;

	while (42)
	{
	while (SDL_PollEvent(&ev))
	{
		make = 0;
		printf("non\n");
		if (ev.type == SDL_QUIT)
				fun_exit(ren, win);		
		if (ev.key.keysym.scancode == SDL_SCANCODE_W)
		{
			if (worldMap[(int)(all->play_pos.x + all->play_vec.x * SPEED)][(int)all->play_pos.y] == 0)
				all->play_pos.x += all->play_vec.x * SPEED;
			if (worldMap[(int)all->play_pos.x][(int)(all->play_pos.y + all->play_vec.y * SPEED)] == 0)
				all->play_pos.y += all->play_vec.y * SPEED;
			make = 1;
		}
		else if (ev.key.keysym.scancode == SDL_SCANCODE_S)
		{
			if (worldMap[(int)(all->play_pos.x - all->play_vec.x * SPEED)][(int)all->play_pos.y] == 0)
				all->play_pos.x -= all->play_vec.x * SPEED;
			if (worldMap[(int)all->play_pos.x][(int)(all->play_pos.y - all->play_vec.y * SPEED)] == 0)
				all->play_pos.y -= all->play_vec.y * SPEED;
			make = 1;
		}
		else if (ev.key.keysym.scancode == SDL_SCANCODE_A)
		{
			old_play_vec_x = all->play_vec.x;
			all->play_vec.x = all->play_vec.x * cos(0.5) - all->play_vec.y * sin(0.5);
			all->play_vec.y = old_play_vec_x * sin(0.5) + all->play_vec.y * (0.5);
			old_cam_plane_x = all->cam_plane.x;
			all->cam_plane.x = all->cam_plane.x * cos(0.5) - all->cam_plane.y * sin(0.5);
			all->cam_plane.y = old_cam_plane_x * sin(0.5) + all->cam_plane.y * cos(0.5);
			make = 1;
		}
		else if (ev.key.keysym.scancode == SDL_SCANCODE_D)
		{
			old_play_vec_x = all->play_vec.x;
			all->play_vec.x = all->play_vec.x * cos(-0.5) - all->play_vec.y * sin(-0.5);
			all->play_vec.y = old_play_vec_x * sin(-0.5) + all->play_vec.y * (-0.5);
			old_cam_plane_x = all->cam_plane.x;
			all->cam_plane.x = all->cam_plane.x * cos(-0.5) - all->cam_plane.y * sin(-0.5);
			all->cam_plane.y = old_cam_plane_x * sin(-0.5) + all->cam_plane.y * cos(-0.5);
			make = 1;
		}
		if (make == 1)
		{
			printf("oui\n");
			all = raycast(ren, worldMap, 0, all);
			SDL_RenderPresent(ren);
		}
	}
	}
}