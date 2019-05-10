/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grota <grota@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:03:46 by grota             #+#    #+#             */
/*   Updated: 2019/05/10 18:27:15 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

typedef struct		s_ptd
{
	double			x;
	double			y;
}					t_ptd;

typedef struct		s_player
{
	t_ptd			play_pos; // Position in **map
	t_ptd			play_coor; // Position of player in the scene
	double			play_angle;
}					t_player;

typedef struct		s_ray_cast
{
	int				wall_size;
	t_ptd			coll_x;
	t_ptd			coll_y;
	t_ptd			wall_end;
	t_ptd			wall_start;
	t_ptd			dist_col_x;
	t_ptd			dist_col_y;
	double			dist_col;
	double			act_angle; // Angle of the ray at instant t
	double			dist_screen;
}					t_ray_cast;

typedef struct		s_sdl
{
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Event		event;
}					t_sdl;

typedef struct		s_env
{
	int				**map;
	int				height;
	int				width;
	t_sdl			sdl;
	t_player		player;
}					t_env;

/*
**	usage/usage.c
*/

void				usage(void);

/*
**	parsing/map.c
*/

void				parse_file(char *file, t_env *env);

/*
**	utils/clean.c
*/

int					free_switch(t_env *env, int code);
int					free_parse(char *row, char **coords, t_env *env, int code);
void				free_split(char **coords);

/*
**	utils/parsing.c
*/

int					size(char **coords);
void				bottom_border(t_env *env);
void				check_row(char *row, t_env *env);
void				limits(char *row, char **coords, t_env *env);

/*
**	Raycasting side-functions
*/

void				draw_rc(t_ptd a, t_ptd b, SDL_Renderer *ren, int clr);
t_ptd				init_ptd(double x, double y);
double				sq(double n);
double				double_abs(double i);
double				my_tan(double angle);
double				rad_angle(double angle);
double				length(t_ptd coll_x, t_ptd coll_y, t_ptd play_coor);
t_player			init_player(void);
t_ray_cast			init_rc(t_player play);
t_ray_cast			*raycast(SDL_Renderer *ren, int map[4][10], int start, t_ray_cast *all);

#endif
