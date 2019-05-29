/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:03:46 by grota             #+#    #+#             */
/*   Updated: 2019/05/29 08:14:36 by nde-jesu         ###   ########.fr       */
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
	t_pos			old;
	t_pos			new;
	int				toggle_mouse;
	unsigned int	curr_time;
	unsigned int	old_time;
}					t_mouse;

typedef struct		s_cam
{
	t_pos			pos;
	t_pos			coord;
	double			angle;
	double			height;
	double			sprint;
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

typedef struct		s_env
{
	int				**map;
	int				height;
	int				width;
	t_sdl			sdl;
	t_cam			cam;
	t_ray			ray;
	int				h;
	int				w;
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
void				setup_raycasting(t_cam *cam, t_ray *ray);
void				cam_setup(t_cam *cam);
void				setup_mouse(t_mouse *mouse, t_env *env);

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

void				move(t_env *env, char *key, int fl);

/*
**	events/movements_calc.c
*/

void				move_forward(t_env *env);
void				move_backward(t_env *env);
void				move_left(t_env *env);
void				move_right(t_env *env);

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

void				resize(t_env *env, t_sdl *sdl);
void				enable_mouse(t_mouse *mouse);

/*
**	Raycasting side-functions
*/

void				draw_rc(t_pos a, t_pos b, t_env *env, t_ray *ray);
double				sq(double n);
double				double_abs(double i);
double				length(t_pos col_x, t_pos col_y, t_pos coord, t_ray *ray);
void				raycast(int **map, t_env *env, t_cam *cam, t_ray *all);
void				fun_exit(SDL_Renderer *ren, SDL_Window *win);
void				y_collisions(t_pos *y, t_pos *py, double angle, t_cam cam);
void				x_collisions(t_pos *x, t_pos *px, double angle, t_cam cam);
double				to_rad(double degre);
#endif
