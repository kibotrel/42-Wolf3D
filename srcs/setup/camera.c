/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 22:50:59 by kibotrel          #+#    #+#             */
/*   Updated: 2019/05/31 14:50:18 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "wolf3d.h"

void	cam_setup(t_cam *cam)
{
	cam->coord.x = (cam->spawn.x + 0.5) * CELL;
	cam->coord.y = (cam->spawn.y + 0.5) * CELL;
	cam->angle = 45;
	cam->offset = 0;
	cam->fov = 60.0;
	cam->sprint = 1.0;
}
