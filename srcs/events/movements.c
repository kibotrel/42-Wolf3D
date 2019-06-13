/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 07:45:26 by nde-jesu          #+#    #+#             */
/*   Updated: 2019/06/13 17:06:34 by reda-con         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "wolf3d.h"

t_pos			init_pos(double x, double y)
{
	t_pos ret;

	ret.x = x;
	ret.y = y;
	return (ret);
}

static void		movements(t_cam *cam, t_pos old, t_env *env, t_pos fl)
{
	t_pos	new;
	double	hit;

	new.x = cam->coord.x + (cos(radians(cam->angle + fl.x)) * (8 * cam->sprint)) * fl.y;
	new.y = cam->coord.y - (sin(radians(cam->angle + fl.x)) * (8 * cam->sprint)) * fl.y;
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

void			move(t_env *env, char *key, t_pos *flags)
{
	t_pos	old;

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
	flags->y = 1;
}
