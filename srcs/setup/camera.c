/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 22:50:59 by kibotrel          #+#    #+#             */
/*   Updated: 2019/05/29 01:20:43 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "wolf3d.h"

void	cam_setup(t_cam *cam)
{
	cam->pos.x = cam->spawn.x;
	cam->pos.y = cam->spawn.y;
	cam->coord.x = cam->pos.x * CELL;
	cam->coord.y = cam->pos.y * CELL;
	cam->angle = 45;
	cam->offset = HEIGHT / 2;
	cam->fov = 60.0;
}
