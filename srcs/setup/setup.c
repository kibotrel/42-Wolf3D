/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 17:17:25 by kibotrel          #+#    #+#             */
/*   Updated: 2019/05/28 23:05:00 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "SDL.h"
#include "libft.h"
#include "env.h"
#include "wolf3d.h"

static void	data_setup(t_env *env)
{
	env->data.east = 0.0;
	env->data.north = M_PI_2;
	env->data.west = M_PI;
	env->data.south = M_PI_2 * 3;
	env->data.two_pi = M_PI * 2;
	ft_bzero(env->inputs, SDL_NUM_SCANCODES);
	env->cam.distance = (WIDTH / 2) / tan(radians(env->cam.fov / 2));
}

void		setup(t_env *env)
{
	sdl_setup(&env->sdl);
	cam_setup(&env->cam);
	data_setup(env);
}
