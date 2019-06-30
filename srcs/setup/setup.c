/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 17:17:25 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/30 17:34:54 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "SDL.h"
#include "libft.h"
#include "env.h"
#include "wolf3d.h"

static int	spawn_setup(t_env *env)
{
	t_pos	pos;
	int		set;

	pos.y = -1;
	set = 0;
	while (++pos.y < env->height)
	{
		pos.x = -1;
		while (++pos.x < env->width)
		{
			if (env->map[(int)pos.y][(int)pos.x] == 9)
			{
				env->cam.spawn.y = pos.y;
				env->cam.spawn.x = pos.x;
				return (1);
			}
			if (!set && env->map[(int)pos.y][(int)pos.x] == 0)
			{
				env->cam.spawn.y = pos.y;
				env->cam.spawn.x = pos.x;
				set = 1;
			}
		}
	}
	return (set);
}

static int	teleport_setup(t_env *env)
{
	int		x;
	int		y;
	int		n;

	y = -1;
	n = 0;
	while (n < 2 && ++y < env->height)
	{
		x = -1;
		while (n < 2 && ++x < env->width)
		{
			if (env->map[y][x] == 2)
			{
				if (n < 2)
				{
					env->tp_start[n].y = y;
					env->tp_start[n].x = x;
				}
				n++;
			}
		}
	}
	return (n == 1 || n > 2 ? 0 : 1);
}

static void	data_setup(t_env *env)
{
	env->data.north = M_PI_2;
	env->data.south = M_PI_2 * 3;
	env->data.two_pi = M_PI * 2;
	ft_bzero(env->inputs, SDL_NUM_SCANCODES);
	env->cam.distance = (WIDTH / 2) / tan(radians(env->cam.fov / 2));
}

static void	mouse_setup(t_env *env)
{
	env->mouse.new.x = env->w / 2;
	env->mouse.new.y = env->h / 2;
	env->mouse.old.x = env->w / 2;
	env->mouse.old.y = env->h / 2;
	env->mouse.toggle_mouse = 1;
	env->mouse.toggle_map = -1;
	env->mouse.old_time = 0;
	env->mouse.nb_frame = 0;
	env->mouse.old_frame = 0;
}

void		set_env(t_env *env)
{
	env->tex_on = -1;
	env->w = WIDTH;
	env->h = HEIGHT;
	if (!spawn_setup(env) && free_switch(env, 1))
		ft_print_error(E_FULL, 19);
	if (!teleport_setup(env) && free_switch(env, 1))
		ft_print_error(E_TP, 20);
	if (!teleport_space(env, -1, 0) && free_switch(env, 1))
		ft_print_error(E_SPACE, 21);
	sdl_setup(&env->sdl, env);
	mouse_setup(env);
	cam_setup(&env->cam);
	data_setup(env);
}
