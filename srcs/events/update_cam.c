/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 18:25:56 by kibotrel          #+#    #+#             */
/*   Updated: 2019/05/27 19:28:08 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "env.h"
#include "wolf3d.h"

void	change_angle(t_env *env, char *key, double *angle, t_pos mouse)
{
	if (key[SDL_SCANCODE_COMMA] || mouse.x < WIDTH / 2)
	{
		*angle += radians(2);
		*angle = (*angle >= env->data.two_pi) ? env->data.two_pi - *angle : *angle;

	}
	else if (key[SDL_SCANCODE_PERIOD] || mouse.x > WIDTH / 2)
	{
		*angle -= radians(2);
		*angle = (*angle < 0) ? env->data.two_pi + *angle : *angle;
	}
	raycast(env);
}

void	change_height(t_env *env, char *key, double *height, int speed, t_pos mouse)
{
	if (key[SDL_SCANCODE_PAGEUP] || mouse.y < HEIGHT / 2)
		*height += 2 * speed;
	else if (key[SDL_SCANCODE_PAGEDOWN] || mouse.y > HEIGHT / 2)
		*height -= 2 * speed;
	if (*height > HEIGHT / 2 * 1.75)
		*height = HEIGHT / 2 * 1.75;
	else if (*height < HEIGHT / 8)
		*height = HEIGHT / 8;
	raycast(env);
}
