/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grota <grota@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:03:46 by grota             #+#    #+#             */
/*   Updated: 2019/05/28 23:28:53 by kibotrel         ###   ########.fr       */
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
	double			fov;
	double			angle;
	double			offset;
	double			distance;
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
	double			step;
	double			distance;
	double			angle;
}					t_ray;

typedef struct		s_sdl
{
	SDL_Window		*win;
	SDL_Renderer	*render;
	SDL_Texture		*texture;
	SDL_Event		event;
	uint32_t		*pixels;
}					t_sdl;

typedef struct		s_data
{
	double			east;
	double			west;
	double			north;
	double			south;
	double			two_pi;
}					t_data;

typedef struct		s_env
{
	int				**map;
	int				height;
	int				width;
	char			inputs[SDL_NUM_SCANCODES];
	t_sdl			sdl;
	t_cam			cam;
	t_ray			ray;
	t_data			data;
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

/*
**	setup/raycasting.c
*/

void				setup_raycasting(t_cam *cam, t_ray *ray);
void				setup_slice(t_ray *ray, t_cam *cam, int x, t_env *env);

/*
**	setup/camera.c
*/

void				cam_setup(t_cam *cam);

/*
**	setup/graphic.c
*/

void				sdl_setup(t_sdl *sdl);

/*
**	utils/clean.c
*/

int					free_switch(t_env *env, int code);
int					free_parse(char *row, char **coords, t_env *env, int code);
void				free_split(char **coords);
void				free_sdl(SDL_Renderer *ren, SDL_Window *win);

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
double				smallest_distance(t_ray *ray, t_data data, t_pos coord);
void				raycast(t_env *env, t_sdl *sdl, t_ray *ray);
void				y_collisions(t_ray *ray, t_cam cam, t_data data);
void				x_collisions(t_ray *ray, t_cam cam, t_data data);
double				radians(double degre);
void				check_collisions(t_ray *rc, int **map, int max_y, int max_x);
#endif
