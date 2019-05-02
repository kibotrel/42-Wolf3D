/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   true_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:30:34 by nde-jesu          #+#    #+#             */
/*   Updated: 2019/05/02 19:22:05 by nde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "env.h"
#include "wolf3d.h"

#define SQUARE_SIZE 64
#include <stdio.h>
#include <unistd.h>

double	rad_angle(double angle)
{
	return (angle * M_PI / 180);
}

float	my_tan(double angle)
{
	return (sin(angle) / cos(angle));
}

static t_ray_cast	init_rc(t_player play)
{
	t_ray_cast	ret;

	ret.dist_screen = (WIN_WIDTH / 2) / my_tan(rad_angle(30));
	if (play.play_angle < 30)
		ret.act_angle = play.play_angle + 330;
	else
		ret.act_angle = play.play_angle - 30;
	return (ret);
}

static t_player	init_player(void)
{
	t_player	ret;

	ret.play_pos.x = 1.5;
	ret.play_pos.y = 3.5;
	ret.play_coor.x = floor(ret.play_pos.x) * SQUARE_SIZE\
					+ (ret.play_pos.x - floor(ret.play_pos.x)) * SQUARE_SIZE;
	ret.play_coor.y = floor(ret.play_pos.y) * SQUARE_SIZE\
					+ (ret.play_pos.y - floor(ret.play_pos.y)) * SQUARE_SIZE;
	ret.play_angle = 90;
	ret.play_angle = (ret.play_angle == 360) ? 0 : ret.play_angle;
	return (ret);
}

static t_ray_cast	y_collisions(t_ray_cast all, t_player play)
{
	if (all.act_angle > 0 && all.act_angle < 180)
		all.coll_y.y = floor(play.play_coor.y / SQUARE_SIZE) * SQUARE_SIZE - 1;
	else
		all.coll_y.y = floor(play.play_coor.y / SQUARE_SIZE)\
					* SQUARE_SIZE + SQUARE_SIZE;
	all.dist_col_y.y = (all.act_angle > 0 && all.act_angle < 180)\
					? -SQUARE_SIZE : SQUARE_SIZE;
	all.coll_y.x = play.play_coor.x + (play.play_coor.y - all.coll_y.y)\
				/ my_tan(rad_angle(all.act_angle));
	all.dist_col_y.x = SQUARE_SIZE / my_tan(rad_angle(all.act_angle));
	all.dist_col_y.x = (all.act_angle > 180 && all.act_angle < 270)\
					? -all.dist_col_y.x : all.dist_col_y.x;
	printf("distY:%f; %f\n", all.dist_col_y.x, all.dist_col_y.y);
	return (all);
}

static t_ray_cast	x_collisions(t_ray_cast all, t_player play)
{
	if (all.act_angle < 90 || all.act_angle > 270)
		all.coll_x.x = floor(play.play_coor.x / SQUARE_SIZE)\
					* SQUARE_SIZE + SQUARE_SIZE;
	else
		all.coll_x.x = floor(play.play_coor.x / SQUARE_SIZE) * SQUARE_SIZE - 1;
	all.dist_col_x.x = (all.act_angle < 90 || all.act_angle > 270)\
					? SQUARE_SIZE : -SQUARE_SIZE;
	all.coll_x.y = play.play_coor.y + (play.play_coor.x - all.coll_x.x)\
				* my_tan(rad_angle(all.act_angle));
	all.dist_col_x.y = SQUARE_SIZE * my_tan(rad_angle(all.act_angle));
	all.dist_col_x.y = (all.act_angle > 0 && all.act_angle < 90)\
				? -(all.dist_col_x.y) : all.dist_col_x.y;
	printf("distX:%f; %f\n", all.dist_col_x.x, all.dist_col_x.y);	
	return (all);
}

static t_ray_cast	check_neg(t_ray_cast all)
{
	all.coll_y.x = (all.coll_y.x < 0) ? 0 : all.coll_y.x;
	all.coll_y.y = (all.coll_y.y < 0) ? 0 : all.coll_y.y;
	all.coll_x.x = (all.coll_x.x < 0) ? 0 : all.coll_x.x;
	all.coll_x.y = (all.coll_x.y < 0) ? 0 : all.coll_x.y;
	return (all);
}

static t_ray_cast	check_coll(t_ray_cast all, int **map)
{
	int		hit_x;
	int		hit_y;

	hit_x = 0;
	hit_y = 0;
	while (hit_x == 0 || hit_y == 0)
	{
		all = check_neg(all);
		if (hit_x == 0 && map[(int)all.coll_x.y / SQUARE_SIZE]\
				[(int)all.coll_x.x / SQUARE_SIZE] != 0)
			hit_x = 1;
		else if (hit_x == 0)
		{
			all.coll_x.x += all.dist_col_x.x;
			all.coll_x.y += all.dist_col_x.y;
		}
		if (hit_y == 0 && map[(int)all.coll_y.y / SQUARE_SIZE]\
				[(int)all.coll_y.x / SQUARE_SIZE] != 0)
			hit_y = 1;
		else if (hit_y == 0)
		{
			all.coll_y.x += all.dist_col_y.x;
			all.coll_y.y += all.dist_col_y.y;
		}
	}
 	printf("X: %i; %i\nY: %i; %i\n", (int)all.coll_x.x/64, (int)all.coll_x.y/64, (int)all.coll_y.x/64, (int)all.coll_y.y/64);
	return (all);
}

void		true_raycast(int **map, SDL_Renderer *ren)
{
	int			x;
	t_player	play;
	t_ray_cast	all;
	int			wall_size;
	t_ptd		wall_start;
	t_ptd		wall_end;
	// double		perp;

// (void)ren;
	x = -1;
	play = init_player();
	all = init_rc(play);
	while (++x < WIN_WIDTH)
	{
		// if (play.play_angle > 45 && play.play_angle <= 135)
		// 	perp = 90;
		// else if (play.play_angle > 135 && play.play_angle <= 225)
		// 	perp = 180;
		// else if (play.play_angle > 225 && play.play_angle <= 315)
		// 	perp = 270;
		// else
		// 	perp = 0;
		all = y_collisions(all, play);
		all = x_collisions(all, play);
		all = check_coll(all, map);
		
		// all.dist_col = sqrt(pow(all.coll_x.x - play.play_pos.x, 2) 
		// + pow(all.coll_x.y - play.play_pos.y, 2));
		// if (all.dist_col > sqrt(pow(all.coll_y.x - play.play_pos.x
		// , 2) + pow(all.coll_y.y - play.play_pos.y, 2)))
		// 	all.dist_col = sqrt(pow(all.coll_y.x - play.play_pos.x
		// 	, 2) + pow(all.coll_y.y - play.play_pos.y, 2));
		all.dist_col = ()
		// all.dist_col = double_abs(play.play_coor.x - all.coll_x.x) / cos(all.act_angle) /*=
		// 	double_abs(play.play_coor.y - all.coll_x.y) / sin(all.act_angle)*/;
		// if (all.dist_col > double_abs(play.play_coor.x - all.coll_y.x) / cos(all.act_angle) /*=
		// double_abs(play.play_coor.y - all.coll_y.y) / sin(all.act_angle)*/)
		// 	all.dist_col = double_abs(play.play_coor.x - all.coll_y.x) / cos(all.act_angle) /*+
		// 	double_abs(play.play_coor.y - all.coll_y.y) / sin(all.act_angle)*/;

		// printf("X: %f; %f\nY: %f; %f\n", all.coll_x.x/64, all.coll_x.y/64, all.coll_y.x/64, all.coll_y.y/64);
		// printf("avant: %f\n", all.dist_col);		
		// if (all.act_angle < perp)
			// all.dist_col *= cos(rad_angle(all.act_angle - play.play_angle));
		// else
			// all.dist_col *= cos(rad_angle(all.act_angle - play.play_angle));
		// printf("apres: %f\n", all.dist_col);		
		wall_size = ceil((SQUARE_SIZE / all.dist_col) * all.dist_screen);
		wall_start.x = WIN_WIDTH - x;
		wall_start.y = (WIN_HEIGHT / 2) - (wall_size / 2);
		wall_end.x = WIN_WIDTH - x;
		wall_end.y = wall_start.y + wall_size;
		draw_line(wall_start, wall_end, ren);
		all.act_angle += 60.0 / WIN_WIDTH;
	}
	SDL_RenderPresent(ren);
 }

int		main(void)
{
	int	**worldMap;
	SDL_Window	*win;
	SDL_Renderer 	*ren;
	SDL_Event		ev;
	int	x;
	int	y;

	x = 0;
	SDL_Init(SDL_INIT_VIDEO);
	if (SDL_CreateWindowAndRenderer(WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_RESIZABLE,
	&win, &ren) == -1)
		return (1);
	worldMap = malloc(sizeof(int*) * 4);
	while (x < 4)
		worldMap[x++] = malloc(sizeof(int) * 10);
	x = -1;
	while (++x < 4)
	{
		y = -1;
		while (++y < 10)
		{
			if (x == 0 || y == 0 || x == 3 || y == 9)
				worldMap[x][y] = 1;
			else
				worldMap[x][y] = 0;
		}
	}
	SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
	true_raycast(worldMap, ren);
	while (42)
	{
		SDL_PollEvent(&ev);
		if (ev.window.event == SDL_WINDOWEVENT_CLOSE)
			exit(0);
	}
	return (0);
}
