/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 18:25:56 by kibotrel          #+#    #+#             */
/*   Updated: 2019/05/27 18:05:23 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "env.h"
#include "wolf3d.h"

void	change_angle(t_env *env, char *key, double *angle, t_pos mouse)
{
	if (key[SDL_SCANCODE_COMMA] || mouse.x < WIDTH / 2)
		*angle = fmod(*angle + radians(2), radians(360));
	else if (key[SDL_SCANCODE_PERIOD] || mouse.x > WIDTH / 2)
		*angle = fmod(*angle - radians(2), radians(360));
	raycast(env);
}

void	change_height(t_env *env, char *key, double *height, int speed, t_pos mouse)
{
	if (key[SDL_SCANCODE_PAGEUP] || mouse.y < HEIGHT / 2)
		*height += 2 * speed;
	else if (key[SDL_SCANCODE_PAGEDOWN] || mouse.y > HEIGHT / 2)
		*height -= 2 * speed;
	if (*height > HEIGHT_CAM)
		*height = HEIGHT_CAM;
	else if (*height < -HEIGHT_CAM)
		*height = -HEIGHT_CAM;
	raycast(env);
}
