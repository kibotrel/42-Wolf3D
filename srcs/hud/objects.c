/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 23:54:51 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/13 00:15:53 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "wolf3d.h"

void	walls(t_sdl *sdl, t_pos wall, t_pos limit, int x)
{
	while (++wall.y < limit.y)
	{
		wall.x = x * 32 + 15;
		while (++wall.x < limit.x)
			sdl->pixels[(int)(wall.x + wall.y * WIDTH)] = 0xffffff;
	}
}

void	spawn(t_sdl *sdl, t_pos wall, t_pos limit, int x)
{
	while (++wall.y < limit.y)
	{
		wall.x = x * 32 + 15;
		while (++wall.x < limit.x)
			sdl->pixels[(int)(wall.x + wall.y * WIDTH)] = 0xffff00ff;
	}
}

void	end(t_sdl *sdl, t_pos wall, t_pos limit, int x)
{
	while (++wall.y < limit.y)
	{
		wall.x = x * 32 + 15;
		while (++wall.x < limit.x)
			sdl->pixels[(int)(wall.x + wall.y * WIDTH)] = 0xff7fffff;
	}
}
