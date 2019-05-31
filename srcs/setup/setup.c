/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 17:17:25 by kibotrel          #+#    #+#             */
/*   Updated: 2019/05/31 14:34:13 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "SDL.h"
#include "libft.h"
#include "env.h"
#include "wolf3d.h"

static int	spawn_setup(t_env *env)
{
	int	x;
	int	y;
	int set;

	y = -1;
	set = 0;
	while (++y < env->height)
	{
		x = -1;
		while (++x < env->width)
		{
			if (env->map[y][x] == 9)
			{
				env->cam.spawn.y = y;
				env->cam.spawn.x = x;
				return (1);
			}
			if (!set && env->map[y][x] == 0)
			{
				env->cam.spawn.y = y;
				env->cam.spawn.x = x;
				set = 1;
			}
		}
	}
	return (set);
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
	env->mouse.old_time = 0;
}

void		setup(t_env *env)
{
	env->w = WIDTH;
	env->h = HEIGHT;
	if (!spawn_setup(env) && free_switch(env, 1))
		ft_print_error(ERR_FULL, 19);
	sdl_setup(&env->sdl, env);
	mouse_setup(env);
	cam_setup(&env->cam);
	data_setup(env);
}
