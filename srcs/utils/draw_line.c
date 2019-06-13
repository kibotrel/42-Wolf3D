/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 08:13:32 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/13 09:04:55 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "env.h"
#include "wolf3d.h"

static t_line	setup_params(t_pos a, t_pos b)
{
	t_line	params;

	params.sign_y = (a.y < b.y ? 1 : -1);
	params.sign_x = (a.x < b.x ? 1 : -1);
	params.delta_y = fabs(b.y - a.y);
	params.delta_x = fabs(b.x - a.x);
	params.offset = params.delta_x - params.delta_y;
	params.error = 0;
	return (params);
}

static int		clip_wall(t_sdl *sdl, int x, int y)
{
	if (sdl->pixels[x + y * WIDTH] != 0xffffff)
	{
		sdl->pixels[x + y * WIDTH] = 0xffffff00;
		return (0);
	}
	return (1);

}
void			draw_line(t_pos a, t_pos b, t_env *env)
{
	t_line	params;
	t_pos	p;

	params = setup_params(a, b);
	p = a;
	while (p.y != b.y || p.x != b.x)
	{
		if (clip_wall(&env->sdl, p.x, p.y))
			return ;
		if ((params.error = params.offset * 2) > -params.delta_y)
		{
			params.offset -= params.delta_y;
			p.x += params.sign_x;
		}
		if (params.error < params.delta_x)
		{
			params.offset += params.delta_x;
			p.y += params.sign_y;
		}
		if (clip_wall(&env->sdl, p.x, p.y))
			return ;
	}
}
