/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 07:45:26 by nde-jesu          #+#    #+#             */
/*   Updated: 2019/07/10 15:28:39 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "wolf3d.h"
#include <math.h>

static void		update_pos(t_cam *cam, t_pos old, t_env *env, t_pos fl)
{
	t_pos	new;
	double	hit;

	new.x = cam->coord.x
		+ (cos(radians(cam->angle + fl.x)) * (2 * cam->sprint)) * fl.y;
	new.y = cam->coord.y
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

void			move(t_env *env, char *key, t_pos *flags)
{
	t_pos	old;
	t_pos	new;

	old.x = env->cam.coord.x;
	old.y = env->cam.coord.y;
	if (key[SDL_SCANCODE_W])
		update_pos(&env->cam, old, env, init_pos(0, 1));
	if (key[SDL_SCANCODE_S])
		update_pos(&env->cam, old, env, init_pos(0, -1));
	if (key[SDL_SCANCODE_A])
		update_pos(&env->cam, old, env, init_pos(90, 1));
	if (key[SDL_SCANCODE_D])
		update_pos(&env->cam, old, env, init_pos(90, -1));
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
