/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 14:57:54 by kibotrel          #+#    #+#             */
/*   Updated: 2019/04/26 10:18:06 by nde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "env.h"
#include "wolf3d.h"
#include "SDL.h"

void	fun_exit(SDL_Renderer *ren, SDL_Window *win)
{
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	exit(0);
}

double	double_abs(double i)
{
	if (i >= 0)
		return (i);
	else
		return (-1 * i);
}

void check_wall_color(SDL_Renderer *ren, int wall, int wall_side)
{
	int darker;

	darker = 1;
	if (wall_side == 1)
		darker = 2;
 	if (wall == 0)
		SDL_SetRenderDrawColor(ren, 255 / darker, 0 / darker, 0 / darker, 255);
	else if (wall == 1)
		SDL_SetRenderDrawColor(ren, 0 / darker, 255 / darker, 0 / darker, 255);
	else if (wall == 2)
		SDL_SetRenderDrawColor(ren, 0 / darker, 0 / darker, 255 / darker, 255);
	else if (wall == 3)
		SDL_SetRenderDrawColor(ren, 255 / darker, 255 / darker, 0 / darker, 255);
	else if (wall == 4)
		SDL_SetRenderDrawColor(ren, 255 / darker, 0 / darker, 255 / darker, 255);
	
		
}

void	raycast(SDL_Renderer *ren, int map[24][24], double play_pos_x, double play_pos_y, double play_vec_x, double play_vec_y)
{
	double 	cam_plane_x = 0;
	double 	cam_plane_y = 0.66;
	double 	cam_x;
	double 	ray_dir_x;
	double 	ray_dir_y;
	int 	map_x;
	int 	map_y;
	double 	len_next_side_x;
	double 	len_next_side_y;
	double 	delta_dist_x;
	double 	delta_dist_y;
	double 	wall_dist;
	int		step_x;
	int		step_y;
	int		hit = 0;
	int		wall_side;
	int 	line_height;
	int		line_draw_start;
	int		line_draw_end;


	for (int x = 0; x < WIN_WIDTH; x++)
	{
		// Init
		cam_x = 2 * x / (double)WIN_WIDTH - 1;
		ray_dir_x = play_vec_x + cam_plane_x * cam_x;
		ray_dir_y = play_vec_y + cam_plane_y * cam_x;
		map_x = (int)play_pos_x;
		map_y = (int)play_pos_y;
		delta_dist_x = double_abs(1 / ray_dir_x);
		delta_dist_y = double_abs(1 / ray_dir_y);

		if (ray_dir_x < 0)
		{
			step_x = -1;
			len_next_side_x = (play_pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			len_next_side_x = (map_x + 1.0 - play_pos_x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			len_next_side_y = (play_pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			len_next_side_y = (map_y + 1.0 - play_pos_y) * delta_dist_y;
		}
		// DDA Algo
		while (hit == 0)
		{
			if (len_next_side_x < len_next_side_y)
			{
				len_next_side_x += delta_dist_x;
				map_x +=step_x;
				wall_side = 0;
			}
			else
			{
				len_next_side_y += delta_dist_y;
				map_y +=step_y;
				wall_side = 1;
			}
			// Check if wall was hit
			if (map[map_x][map_y] > 0)
				hit = 1;
		}
		if (wall_side == 0)
			wall_dist = (map_x - play_pos_x + (1 - step_x) / 2) / ray_dir_x;
		else
			wall_dist = (map_y - play_pos_y + (1 - step_y) / 2) / ray_dir_y;
		line_height = (int)(WIN_HEIGHT / wall_dist);
		line_draw_start = -line_height / 2 + WIN_HEIGHT / 2;
		line_draw_end = line_height / 2 + WIN_HEIGHT / 2;
		if (line_draw_start < 0)
			line_draw_start = 0;
		if (line_draw_end > WIN_HEIGHT)
			line_draw_end = WIN_HEIGHT - 1;
		check_wall_color(ren, map[map_x][map_y], wall_side);
		// Draw Vertical Line
		SDL_RenderDrawLine(ren, x, line_draw_start, x, line_draw_end);
	}
}
int	main(void)
{
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Event		ev;

	double 	play_pos_x = 2.0;
	double 	play_pos_y = 2.0;
	double 	play_vec_x = 0;
	double 	play_vec_y = -1;
	double	mov_speed;
	double	rot_speed;

	double act_time = 0;
	double old_time = 0;
	double frame_time;

	int worldMap[24][24]=
	{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};



	SDL_Init(SDL_INIT_VIDEO);
	if (SDL_CreateWindowAndRenderer(WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_RESIZABLE, &win, &ren) == -1)
		return (1);
	while (42)
	{
		old_time = act_time;
		act_time = (double)SDL_GetTicks();
		frame_time = (act_time - old_time) / 1000.0;
		printf("%i", 1.0 / frame_time);
		mov_speed = frame_time * 5.0;
		rot_speed = frame_time * 3.0;
		// Read keys
	/*	while (SDL_PollEvent(&ev))
		{
			if (ev.type == SDL_QUIT)
				fun_exit(ren, win);
			if (ev.type == SDL_KEYDOWN)
			{
				if (ev.key.keysym.scancode == SDL_SCANCODE_W)
				{
					if (worldMap[(int)(pos)][])
				}
				else if (ev.key.keysym.scancode == SDL_SCANCODE_S)
				else if (ev.key.keysym.scancode == SDL_SCANCODE_A)
				else if (ev.key.keysym.scancode == SDL_SCANCODE_D)

				
			
			}
		}*/
		raycast(ren, worldMap, play_pos_x, play_pos_y, play_vec_x, play_vec_y);
		SDL_RenderPresent(ren);
	}
}
