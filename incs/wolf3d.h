/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:03:46 by grota             #+#    #+#             */
/*   Updated: 2019/05/07 16:47:11 by reda-con         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "SDL.h"
/*
**	usage/usage.c
*/

typedef struct	s_ptd
{
	double	x;
	double	y;
}				t_ptd;

typedef struct	s_player
{
	t_ptd	play_pos;
	int		play_angle;
	t_ptd	play_coor;
}				t_player;

typedef struct	s_ray_cast
{
	double	dist_screen;
	t_ptd	dist_col_x;
	t_ptd	dist_col_y;
	t_ptd	coll_x;
	t_ptd	coll_y;
	double	dist_col;
	double	act_angle;
}				t_ray_cast;

void	fun_exit(SDL_Renderer *ren, SDL_Window *win);
void	usage(void);

/*
**	Raycasting side-functions
*/

t_ray_cast	*raycast(SDL_Renderer *ren, int map[4][10], int start, t_ray_cast *all);
void 		draw_line(t_ptd a, t_ptd b, SDL_Renderer *ren);
void		check_wall_color(SDL_Renderer *ren, int wall, int wall_side);
void		control(t_ray_cast *all, int worldMap[4][10], SDL_Window *win, SDL_Renderer *ren);
double		double_abs(double i);
t_ptd		init_ptd(double x, double y);
double		my_tan(double angle);
double		rad_angle(double angle);
t_player	init_player(void);
t_ray_cast	init_rc(t_player plau);

#endif
