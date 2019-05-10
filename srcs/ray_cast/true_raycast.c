/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   true_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:30:34 by nde-jesu          #+#    #+#             */
/*   Updated: 2019/05/10 16:19:44 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "wolf3d.h"

static t_ray_cast	y_collisions(t_ray_cast all, t_player *play)
{
	if (all.act_angle > 0 && all.act_angle < 180)
		all.coll_y.y = floor(play->play_coor.y / SQUARE_SIZE) * SQUARE_SIZE - 1;
	else
		all.coll_y.y = floor(play->play_coor.y / SQUARE_SIZE) * SQUARE_SIZE + SQUARE_SIZE;
	all.dist_col_y.y = (all.act_angle > 0 && all.act_angle < 180) ? -SQUARE_SIZE : SQUARE_SIZE;
	all.coll_y.x = play->play_coor.x + (play->play_coor.y - all.coll_y.y) / my_tan(rad_angle(all.act_angle));
	all.dist_col_y.x = SQUARE_SIZE / my_tan(rad_angle(all.act_angle));
	all.dist_col_y.x = (all.act_angle > 180 && all.act_angle < 270) ? -all.dist_col_y.x : all.dist_col_y.x;
	return (all);
}

static t_ray_cast	x_collisions(t_ray_cast all, t_player *play)
{
	if (all.act_angle < 90 || all.act_angle > 270)
		all.coll_x.x = floor(play->play_coor.x / SQUARE_SIZE) * SQUARE_SIZE + SQUARE_SIZE;
	else
		all.coll_x.x = floor(play->play_coor.x / SQUARE_SIZE) * SQUARE_SIZE - 1;
	all.dist_col_x.x = (all.act_angle < 90 || all.act_angle > 270) ? SQUARE_SIZE : -SQUARE_SIZE;
	all.coll_x.y = play->play_coor.y + (play->play_coor.x - all.coll_x.x) * my_tan(rad_angle(all.act_angle));
	all.dist_col_x.y = SQUARE_SIZE * my_tan(rad_angle(all.act_angle));
	all.dist_col_x.y = (all.act_angle > 0 && all.act_angle < 90) ? -(all.dist_col_x.y) : all.dist_col_x.y;
	return (all);
}

static t_ray_cast	check_neg(t_ray_cast all)
{
	all.coll_y.x = (all.coll_y.x < 0) ? 0 : all.coll_y.x;
	all.coll_y.y = (all.coll_y.y < 0) ? 0 : all.coll_y.y;
	all.coll_x.x = (all.coll_x.x < 0) ? 0 : all.coll_x.x;
	all.coll_x.y = (all.coll_x.y < 0) ? 0 : all.coll_x.y;
	all.coll_y.x = (all.coll_y.x > 9 * SQUARE_SIZE) ? 9 * SQUARE_SIZE : all.coll_y.x;
	all.coll_y.y = (all.coll_y.y > 9 * SQUARE_SIZE) ? 9 * SQUARE_SIZE : all.coll_y.y;
	all.coll_x.x = (all.coll_x.x > 9 * SQUARE_SIZE) ? 9 * SQUARE_SIZE : all.coll_x.x;
	all.coll_x.y = (all.coll_x.y > 9 * SQUARE_SIZE) ? 9 * SQUARE_SIZE : all.coll_x.y;
	return (all);
}

static t_ray_cast	check_coll(t_ray_cast all, int **map)
{
	t_ptd	hit;

	hit.x = 0;
	hit.y = 0;
	while (hit.x == 0 || hit.y == 0)
	{
		all = check_neg(all);
		if (hit.x == 0 && map[(int)all.coll_x.y / SQUARE_SIZE][(int)all.coll_x.x / SQUARE_SIZE] != 0)
			hit.x = 1;
		else if (hit.x == 0)
		{
			all.coll_x.x += all.dist_col_x.x;
			all.coll_x.y += all.dist_col_x.y;
		}
		if (hit.y == 0 && map[(int)all.coll_y.y / SQUARE_SIZE][(int)all.coll_y.x / SQUARE_SIZE] != 0)
			hit.y = 1;
		else if (hit.y == 0)
		{
			all.coll_y.x += all.dist_col_y.x;
			all.coll_y.y += all.dist_col_y.y;
		}
	}
	return (all);
}

int					check_color(double angle)
{
	if (angle <= 45 || angle > 315)
		return (RED);
	else if (angle <= 315 && angle > 225)
		return (GREEN);
	else if (angle <= 225 && angle > 135)
		return (BLUE);
	else
		return (YELLOW);
}

void				true_raycast(int **map, SDL_Renderer *ren, t_player *play)
{
	int			x;
	t_ray_cast	all;
	SDL_Texture	*tex;
	SDL_Rect	rect;

	all = init_rc(*play);
	rect.x = 0;
	rect.y = 0;
	x = -1;
	tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WIN_WIDTH, WIN_HEIGHT);
	SDL_SetRenderTarget(ren, tex);
	while (++x < WIN_WIDTH)
	{
		all = y_collisions(all, play);
		all = x_collisions(all, play);
		all = check_coll(all, map);
		all.dist_col = length(all.coll_x, all.coll_y, play->play_coor);
		all.dist_col *= cos(rad_angle(play->play_angle - all.act_angle));
		all.wall_size = ceil((SQUARE_SIZE / all.dist_col) * all.dist_screen);
		all.wall_start.x = WIN_WIDTH - x;
		all.wall_start.y = (WIN_HEIGHT / 2) - (all.wall_size / 2);
		all.wall_end.x = WIN_WIDTH - x;
		all.wall_end.y = all.wall_start.y + all.wall_size;
		draw_rc(all.wall_start, all.wall_end, ren, 0x646464);
		all.act_angle += 60.0 / WIN_WIDTH;
	}
	SDL_SetRenderTarget(ren, NULL);
	SDL_QueryTexture(tex, NULL, NULL, &rect.w, &rect.h);
	SDL_RenderCopy(ren, tex, NULL, &rect);
	SDL_RenderPresent(ren);
	SDL_DestroyTexture(tex);
}

void				change_angle(t_player *play, SDL_Keysym key)
{
	if (key.sym == SDLK_COMMA)
		play->play_angle += 2;
	else
		play->play_angle -= 2;
}

void				change_mouse_angle(int chg, t_player *play)
{
	if (chg > 0)
		--play->play_angle;
	else
		++play->play_angle;
}

int					main(void)
{
	int				**worldmap;
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Event		ev;
	int				x;
	int				y;
	t_player		play;
	int				neg;
	int				wait;

	x = 0;
	SDL_Init(SDL_INIT_VIDEO);
	if (SDL_CreateWindowAndRenderer(WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_RESIZABLE, &win, &ren) == -1)
		return (1);
	worldmap = malloc(sizeof(int*) * 10);
	while (x < 10)
		worldmap[x++] = malloc(sizeof(int) * 10);
	x = -1;
	while (++x < 10)
	{
		y = -1;
		while (++y < 10)
			worldmap[x][y] = ((x == 0 || y == 0 || x == 9 || y == 9) ? 1 : 0);
	}
	play = init_player();
	worldmap[6][6] = 1;
	true_raycast(worldmap, ren, &play);
	wait = 1;
	while (wait)
	{
		SDL_PollEvent(&ev);
		if (ev.window.event == SDL_WINDOWEVENT_CLOSE || ev.key.keysym.sym == SDLK_ESCAPE)
			wait = 0;
		else if (ev.type == SDL_KEYDOWN)
		{
			if (ev.key.keysym.sym == SDLK_COMMA || ev.key.keysym.sym == SDLK_PERIOD)
			{
				change_angle(&play, ev.key.keysym);
				true_raycast(worldmap, ren, &play);
			}
			else if (ev.key.keysym.sym == SDLK_w)
			{
				neg = ((play.play_angle < 90 && play.play_angle > 0) || (play.play_angle > 180 && play.play_angle < 270)) ? -1 : 1;
				play.play_coor.x += cos(rad_angle(play.play_angle)) * 10 * neg;
				play.play_coor.y -= sin(rad_angle(play.play_angle)) * 10;
				true_raycast(worldmap, ren, &play);
			}
			else if (ev.key.keysym.sym == SDLK_s)
			{
				neg = ((play.play_angle < 90 && play.play_angle > 0) || (play.play_angle > 180 && play.play_angle < 270)) ? -1 : 1;
				play.play_coor.x -= cos(rad_angle(play.play_angle)) * 10 * neg;
				play.play_coor.y += sin(rad_angle(play.play_angle)) * 10;
				true_raycast(worldmap, ren, &play);
			}
			else if (ev.key.keysym.sym == SDLK_a)
			{
				neg = ((play.play_angle + 90 < 90 && play.play_angle + 90 > 0) || (play.play_angle + 90 > 180 && play.play_angle + 90 < 270)) ? -1 : 1;
				play.play_coor.x += cos(rad_angle(play.play_angle + 90)) * 10;
				play.play_coor.y -= sin(rad_angle(play.play_angle + 90)) * 10;
				true_raycast(worldmap, ren, &play);
			}
			else if (ev.key.keysym.sym == SDLK_d)
			{
				neg = ((play.play_angle + 90 < 90 && play.play_angle + 90 > 0) || (play.play_angle + 90 > 180 && play.play_angle + 90 < 270)) ? -1 : 1;
				play.play_coor.x -= cos(rad_angle(play.play_angle + 90)) * 10;
				play.play_coor.y += sin(rad_angle(play.play_angle + 90)) * 10;
				true_raycast(worldmap, ren, &play);
			}
		}
	}
	fun_exit(ren, win);
	return (0);
}
