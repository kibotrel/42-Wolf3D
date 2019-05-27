/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grota <grota@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:03:46 by grota             #+#    #+#             */
/*   Updated: 2019/05/24 16:10:33 by reda-con         ###   ########.fr       */
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
	t_pos			pos;
	t_pos			coord;
	double			angle;
	double			height;
}					t_cam;

typedef struct		s_wall
{
	double			size;
	t_pos			end;
	t_pos			start;
	int				color;
}					t_wall;

typedef struct		s_ray
{
	t_pos			gap_x;
	t_pos			gap_y;
	t_pos			hit_x;
	t_pos			hit_y;
	t_wall			wall;
	double			dist;
	double			angle;
	double			screen;
}					t_ray;

typedef struct		s_sdl
{
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Texture		*text;
	SDL_Event		event;
	uint32_t		*pixels;
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

void				hooks(t_env *env, int *loop, char *key);

/*
**	parsing/map.c
*/

void				parse_file(char *file, t_env *env);

/*
**	setup/setup.c
*/

void				setup(t_env *env);
void				setup_raycasting(t_cam *cam, t_ray *ray);
void				cam_setup(t_cam *cam);

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
void				move(t_env *env, char *key);
/*
**	events/update_cam.c
*/

void				change_angle(t_env *env, char  *key, double *angle, t_pos mouse);
void				change_height(t_env *env, char *key, double *height, int speed, t_pos mouse);

/*
**	events/place_blocks.c
*/

void				place_block(t_env *env);

/*
**	Raycasting side-functions
*/

void				draw_rc(t_pos a, t_pos b, t_sdl sdl, int clr);
double				sq(double n);
double				double_abs(double i);
double				length(t_pos col_x, t_pos col_y, t_pos coord, t_ray *ray);
void				raycast(int **map, t_env *env, t_cam *cam, t_ray *all);
void				fun_exit(SDL_Renderer *ren, SDL_Window *win);
void				y_collisions(t_pos *y, t_pos *py, double angle, t_cam cam);
void				x_collisions(t_pos *x, t_pos *px, double angle, t_cam cam);
double				to_rad(double degre);
#endif
