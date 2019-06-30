/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 07:45:26 by nde-jesu          #+#    #+#             */
/*   Updated: 2019/06/30 18:35:09 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "wolf3d.h"
#include <math.h>

static void		movements(t_cam *cam, t_pos old, t_env *env, t_pos fl)
{
	t_pos	new;
	double	hit;

	new.x = cam->coord.x\
			+ (cos(radians(cam->angle + fl.x)) * (2 * cam->sprint)) * fl.y;
	new.y = cam->coord.y\
			- (sin(radians(cam->angle + fl.x)) * (2 * cam->sprint)) * fl.y;
	if (new.y < old.y)
		hit = -HITBOX;
	else
		hit = HITBOX;
	if (env->map[(int)(new.y / CELL + hit)][(int)old.x / CELL] != 1)
		cam->coord.y = new.y;
	if (new.x < old.x)
		hit = -HITBOX;
	else
		hit = HITBOX;
	if (env->map[(int)old.y / CELL][(int)(new.x / CELL + hit)] != 1)
		cam->coord.x = new.x;
}

static void		display_time(unsigned int time)
{
	double	sec;

	ft_putstr("\ne");
	ft_putendl("\033[33mGOOD JOB, YOU WON !\33[0m");
	ft_putstr("\033[1;31mYour time is : \033[0m\033[35m");
	sec = time / 1000;
	if (sec > 60)
	{
		ft_putnbr(sec / 60);
		sec = fmod(sec, 60);
		ft_putchar('\'');
	}
	ft_putnbr(sec);
	ft_putchar('\"');
	ft_putnbr(fmod(time, 1000));
	ft_putstr("\n");
	ft_putstr("\033[0m");
}

static void		teleport_player(t_env *env, t_pos pos)
{
	pos.x = floor(pos.x / CELL);
	pos.y = floor(pos.y / CELL);
	if (pos.x == env->tp_start[0].x && pos.y == env->tp_start[0].y)
	{
		env->cam.coord = env->tp_end[1].pos;
		env->cam.angle = env->tp_end[1].angle;
	}
	if (pos.x == env->tp_start[1].x && pos.y == env->tp_start[1].y)
	{
		env->cam.coord = env->tp_end[0].pos;
		env->cam.angle = env->tp_end[0].angle;
	}
}

void			move(t_env *env, char *key, t_pos *flags)
{
	t_pos	old;
	t_pos	new;

	old.x = env->cam.coord.x;
	old.y = env->cam.coord.y;
	if (key[SDL_SCANCODE_W])
		movements(&env->cam, old, env, init_pos(0, 1));
	if (key[SDL_SCANCODE_S])
		movements(&env->cam, old, env, init_pos(0, -1));
	if (key[SDL_SCANCODE_A])
		movements(&env->cam, old, env, init_pos(90, 1));
	if (key[SDL_SCANCODE_D])
		movements(&env->cam, old, env, init_pos(90, -1));
	new.x = env->cam.coord.x;
	new.y = env->cam.coord.y;
	if (env->map[(int)new.y / CELL][(int)new.x / CELL] == 2)
		teleport_player(env, env->cam.coord);
	if (env->map[(int)new.y / CELL][(int)new.x / CELL] == 5)
	{
		display_time(env->mouse.cur_frame);
		flags->x = 0;
	}
	flags->y = 1;
}
