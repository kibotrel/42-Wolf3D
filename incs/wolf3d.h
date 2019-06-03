/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grota <grota@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:03:46 by grota             #+#    #+#             */
/*   Updated: 2019/06/03 11:12:58 by reda-con         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "SDL.h"

typedef struct		s_color
{
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;
}					t_color;

typedef struct		s_pos
{
	double			x;
	double			y;
}					t_pos;

typedef struct		s_mouse
{
	int				toggle_mouse;
	t_pos			old;
	t_pos			new;
	unsigned int	curr_time;
	unsigned int	old_time;
}					t_mouse;

typedef struct		s_cam
{
	t_pos			spawn;
	t_pos			coord;
	double			fov;
	double			angle;
	double			offset;
	double			sprint;
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
	t_pos			slope;
	t_wall			wall;
	double			step;
	double			distance;
	double			angle;
	double			screen;
	int				offset;
	int				which_wall;
}					t_ray;

typedef struct		s_sdl
{
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Texture		*text;
	SDL_Surface		*surf[4];
	SDL_Event		event;
	uint32_t		*pixels;
}					t_sdl;

typedef struct		s_data
{
	double			north;
	double			south;
	double			two_pi;
}					t_data;

typedef struct		s_env
{
	int				h;
	int				w;
	int				**map;
	int				height;
	int				width;
	char			inputs[SDL_NUM_SCANCODES];
	t_sdl			sdl;
	t_cam			cam;
	t_ray			ray;
	t_data			data;
	t_mouse			mouse;
}					t_env;

/*
**	core/hooks.c
*/

void				hooks(t_env *env, t_pos *flags, char *key, t_mouse *mouse);

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

void				setup_raycasting(t_cam *cam, t_ray *ray, int width);
void				setup_slice(t_ray *ray, t_cam *cam, int x, t_env *env);

/*
**	setup/camera.c
*/

void				cam_setup(t_cam *cam);
void				setup_mouse(t_mouse *mouse, t_env *env);

/*
**	setup/graphic.c
*/

void				sdl_setup(t_sdl *sdl, t_env *env);

/*
**	utils/clean.c
*/

int					free_switch(t_env *env, int code);
int					free_parse(char *row, char **coords, t_env *env, int code);
void				free_split(char **coords);
void				free_sdl(t_env *env, int state, char *error, int code);

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

void				change_angle(char  *key, double *angle, t_pos mouse, t_env *env);
void				change_height(char *key, t_env *env, int speed, t_pos mouse);

/*
**	events/place_blocks.c
*/

void				place_block(t_env *env);

/*
**	events/resize.c
*/

void				enable_mouse(t_mouse *mouse);
void				resize(t_env *env, t_sdl *sdl);

/*
**	maths/maths.c
*/

double				radians(double degre);
double				smallest_distance(t_ray *ray, t_data data, t_pos coord);

/*
**	raycasting/raycast.c
*/

void				raycast(t_env *env, t_ray *ray);

/*
**	raycasting/collisions.c
*/

void				y_collisions(t_ray *ray, t_cam cam);
void				x_collisions(t_ray *ray, t_cam cam, t_data data);
void				check_collisions(t_ray *ray, int **map, int y, int x);

/*
**	hud/hud.c
*/

void				hud(t_env *env);

/*
**	hud/minimap.c
*/

void				minimap(t_env *env);

#endif
