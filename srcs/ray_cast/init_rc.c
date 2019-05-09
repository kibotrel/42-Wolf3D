/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reda-con <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 16:44:05 by reda-con          #+#    #+#             */
/*   Updated: 2019/05/09 10:44:07 by reda-con         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "wolf3d.h"

t_ray_cast	init_rc(t_player play)
{
	t_ray_cast	ret;

	ret.dist_screen = (WIN_WIDTH / 2) / my_tan(rad_angle(30));
	if (play.play_angle < 30)
		ret.act_angle = play.play_angle + 330;
	else
		ret.act_angle = play.play_angle - 30;
	return (ret);
}

t_player	init_player(void)
{
	t_player	ret;

	ret.play_pos.x = 8.5;
	ret.play_pos.y = 8.5;
	ret.play_coor.x = floor(ret.play_pos.x) * SQUARE_SIZE\
		+ (ret.play_pos.x - floor(ret.play_pos.x)) * SQUARE_SIZE;
	ret.play_coor.y = floor(ret.play_pos.y) * SQUARE_SIZE\
		+ (ret.play_pos.y - floor(ret.play_pos.y)) * SQUARE_SIZE;
	ret.play_angle = 135;
	ret.play_angle = (ret.play_angle == 360) ? 0 : ret.play_angle;
	return (ret);
}
