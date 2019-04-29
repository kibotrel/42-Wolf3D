/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:03:46 by grota             #+#    #+#             */
/*   Updated: 2019/04/29 10:32:37 by nde-jesu         ###   ########.fr       */
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

typedef struct	s_ray_cast
{
	double 	cam_x;
	int		wall_side;
	int		wall_dist;
	int		line_height;
	t_ptd	line_draw;
	t_ptd	step;
	t_ptd	len_next_side;
	t_ptd	ray_dir;
	t_ptd	map_co;
	t_ptd	delta_dist;
	t_ptd	cam_plane;
	t_ptd	play_vec;
	t_ptd	play_pos;
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

#endif
