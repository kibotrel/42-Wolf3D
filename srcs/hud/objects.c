/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 23:54:51 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/27 09:36:48 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "wolf3d.h"

void	walls(t_env *env, t_pos wall, t_pos limit, int x)
{
	while (++wall.y <= limit.y)
	{
		wall.x = x * (4 * env->factor) + 15;
		while (++wall.x <= limit.x)
			env->sdl.pixels[(int)(wall.x + wall.y * env->w)] = 0xffffff;
	}
}

void	spawn(t_env *env, t_pos wall, t_pos limit, int x)
{
	while (++wall.y <= limit.y)
	{
		wall.x = x * (4 * env->factor) + 15;
		while (++wall.x <= limit.x)
			env->sdl.pixels[(int)(wall.x + wall.y * env->w)] = 0xffff00ff;
	}
}

void	finish(t_env *env, t_pos wall, t_pos limit, int x)
{
	while (++wall.y <= limit.y)
	{
		wall.x = x * (4 * env->factor) + 15;
		while (++wall.x <= limit.x)
			env->sdl.pixels[(int)(wall.x + wall.y * env->w)] = 0xff7fffff;
	}
}
