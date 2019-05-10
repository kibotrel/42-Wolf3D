/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   true_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:30:34 by nde-jesu          #+#    #+#             */
/*   Updated: 2019/05/10 19:16:07 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "wolf3d.h"

static void	check_bounds(t_ray_cast *all)
{
	all->coll_y.x = (all->coll_y.x < 0) ? 0 : all->coll_y.x;
	all->coll_y.y = (all->coll_y.y < 0) ? 0 : all->coll_y.y;
	all->coll_x.x = (all->coll_x.x < 0) ? 0 : all->coll_x.x;
	all->coll_x.y = (all->coll_x.y < 0) ? 0 : all->coll_x.y;
	all->coll_y.x = (all->coll_y.x > 9 * SQUARE_SIZE) ? 9 * SQUARE_SIZE : all->coll_y.x;
	all->coll_y.y = (all->coll_y.y > 9 * SQUARE_SIZE) ? 9 * SQUARE_SIZE : all->coll_y.y;
	all->coll_x.x = (all->coll_x.x > 9 * SQUARE_SIZE) ? 9 * SQUARE_SIZE : all->coll_x.x;
	all->coll_x.y = (all->coll_x.y > 9 * SQUARE_SIZE) ? 9 * SQUARE_SIZE : all->coll_x.y;
}

static void	check_collisions(t_ray_cast *all, int **map)
{
	t_ptd	hit;

	hit.x = 0;
	hit.y = 0;
	while (hit.x == 0 || hit.y == 0)
	{
		check_bounds(all);
		if (hit.x == 0 && map[(int)all->coll_x.y / SQUARE_SIZE][(int)all->coll_x.x / SQUARE_SIZE])
			hit.x = 1;
		else if (hit.x == 0)
		{
			all->coll_x.x += all->dist_col_x.x;
			all->coll_x.y += all->dist_col_x.y;
		}
		if (hit.y == 0 && map[(int)all->coll_y.y / SQUARE_SIZE][(int)all->coll_y.x / SQUARE_SIZE])
			hit.y = 1;
		else if (hit.y == 0)
		{
			all->coll_y.x += all->dist_col_y.x;
			all-.coll_y.y += all->dist_col_y.y;
		}
	}
	return (all);
}

static void	setup_line(t_ray_cast *all, t_player *all, int x)
{
	all->dist_col = length(all->coll_x, all->coll_y, play->play_coor);
	all->dist_col *= cos(play->play_angle - all->act_angle);
	all->wall_size = ceil((SQUARE_SIZE / all->dist_col) * all->dist_screen);
	all->wall_start.x = WIN_WIDTH - x;
	all->wall_start.y = (WIN_HEIGHT / 2) - (all->wall_size / 2);
	all->wall_end.x = WIN_WIDTH - x;
	all->wall_end.y = all->wall_start.y + all->wall_size;
}

void		raycast(int **map, t_sdl *sdl, t_player *play, t_ray_cast *all)
{
	int			x;

	x = -1;
	setup_raycasting(play, all);
	while (++x < WIDTH)
	{
		y_collisions(all, play);
		x_collisions(all, play);
		check_collisions(all, map);
		setup_line(all, play, x);
		draw_rc(all.wall_start, all.wall_end, sdl->ren, DARK_GRAY);
		all.act_angle += (60.0 * RADIAN) / WIN_WIDTH;
	}
	SDL_RenderPresent(ren);
}

// CA BOUGE
void		change_angle(t_player *play, SDL_Keysym key)
{
	if (key.sym == SDLK_COMMA)
		play->play_angle += 2 * RADIAN;
	else
		play->play_angle -= 2 * RADIAN;
}

// BYE BYE
int					main(void)
{
	// int				neg;
	int				wait;
	t_ray_cast		all;

	all.dist_screen = (WIN_WIDTH / 2) / tan(30 * RADIAN);
	raycast(env->map, env->sdl->ren, env->player , &all);

	wait = 1;
	// event loop (NEED TO DEAL WITH RADIAN ANGLES)
	while (wait)
	{
		SDL_PollEvent(&env->sdl->event); // ev = event
		if (ev.window.event == SDL_WINDOWEVENT_CLOSE || ev.key.keysym.sym == SDLK_ESCAPE)
			wait = 0;
		// else if (ev.type == SDL_KEYDOWN)
		// {
		// 	if (ev.key.keysym.sym == SDLK_COMMA || ev.key.keysym.sym == SDLK_PERIOD)
		// 	{
		// 		change_angle(&play, ev.key.keysym);
		// 		true_raycast(worldmap, ren, &play);
		// 	}
		// 	else if (ev.key.keysym.sym == SDLK_w)
		// 	{
		// 		neg = ((play.play_angle < 90 && play.play_angle > 0) || (play.play_angle > 180 && play.play_angle < 270)) ? -1 : 1;
		// 		play.play_coor.x += cos(rad_angle(play.play_angle)) * 10 * neg;
		// 		play.play_coor.y -= sin(rad_angle(play.play_angle)) * 10;
		// 		true_raycast(worldmap, ren, &play);
		// 	}
		// 	else if (ev.key.keysym.sym == SDLK_s)
		// 	{
		// 		neg = ((play.play_angle < 90 && play.play_angle > 0) || (play.play_angle > 180 && play.play_angle < 270)) ? -1 : 1;
		// 		play.play_coor.x -= cos(rad_angle(play.play_angle)) * 10 * neg;
		// 		play.play_coor.y += sin(rad_angle(play.play_angle)) * 10;
		// 		true_raycast(worldmap, ren, &play);
		// 	}
		// 	else if (ev.key.keysym.sym == SDLK_a)
		// 	{
		// 		neg = ((play.play_angle + 90 < 90 && play.play_angle + 90 > 0) || (play.play_angle + 90 > 180 && play.play_angle + 90 < 270)) ? -1 : 1;
		// 		play.play_coor.x += cos(rad_angle(play.play_angle + 90)) * 10;
		// 		play.play_coor.y -= sin(rad_angle(play.play_angle + 90)) * 10;
		// 		true_raycast(worldmap, ren, &play);
		// 	}
		// 	else if (ev.key.keysym.sym == SDLK_d)
		// 	{
		// 		neg = ((play.play_angle + 90 < 90 && play.play_angle + 90 > 0) || (play.play_angle + 90 > 180 && play.play_angle + 90 < 270)) ? -1 : 1;
		// 		play.play_coor.x -= cos(rad_angle(play.play_angle + 90)) * 10;
		// 		play.play_coor.y += sin(rad_angle(play.play_angle + 90)) * 10;
		// 		true_raycast(worldmap, ren, &play);
		// 	}
		// }
	}
	fun_exit(ren, win);
	return (0);
}
