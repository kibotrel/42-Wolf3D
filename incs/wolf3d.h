/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:03:46 by grota             #+#    #+#             */
/*   Updated: 2019/05/14 10:25:34 by reda-con         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "SDL.h"

typedef struct		s_pos
{
	double			x;
	double			y;
}					t_pos;

typedef struct		s_cam
{
	t_pos			pos;	// Position in **map
	t_pos			coord;	// Position of player in the scene
	double			angle;	// Direction
}					t_cam;

typedef struct		s_wall
{
	int				size;
	t_pos			end;
	t_pos			start;
}					t_wall;


typedef struct		s_ray
{
	t_pos			gap_x;	// Shift to the next collumn
	t_pos			gap_y;	// Shift to the next row
	t_pos			hit_x;	// Collisions on columns
	t_pos			hit_y;	// Collisions on rows
	t_wall			wall;
	double			dist;	// True distance between player and nearest wall
	double			angle;	// Angle of the ray at instant t
	double			screen;
}					t_ray;

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
	t_cam			cam;
	t_ray			ray;
}					t_env;

/*
**	core/hooks.c
*/

void				hooks(t_env *env, int *loop);

/*
**	parsing/map.c
*/

void				parse_file(char *file, t_env *env);

/*
**	setup/setup.c
*/

void				setup(t_env *env);
void				setup_raycasting(t_cam *cam, t_ray *ray);


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
**	usage/usage.c
*/

void				usage(void);


/*
**	events/movements.c
*/

void				move_forward(t_env *env, int neg);
void				move_backward(t_env *env, int neg);
void				move_left(t_env *env, int neg);
void				move_right(t_env *env, int neg);


/*
**	events/update_cam.c
*/

void	change_angle(t_env *env, SDL_Keysym key);


/*
**	Raycasting side-functions
*/

void				draw_rc(t_pos a, t_pos b, SDL_Renderer *ren, int clr);
double				sq(double n);
double				double_abs(double i);
double				length(t_pos coll_x, t_pos coll_y, t_pos play_coor);
void				raycast(int **map, t_env *env, t_cam *cam, t_ray *all);
void				fun_exit(SDL_Renderer *ren, SDL_Window *win);
void				y_collisions(t_pos *hit_y, t_pos *gap_y, double angle, t_cam cam);
void				x_collisions(t_pos *hit_x, t_pos *gap_x, double angle, t_cam cam);
#endif
