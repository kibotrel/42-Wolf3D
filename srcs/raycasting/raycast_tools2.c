/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_tools2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reda-con <reda-con@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 11:01:01 by reda-con          #+#    #+#             */
/*   Updated: 2019/05/13 17:56:05 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

double	sq(double n)
{
	return (pow(n, 2));
}

double	length(t_pos coll_x, t_pos coll_y, t_pos play_coor)
{
	double	is_y;
	double	is_x;

	is_x = sqrt(sq(coll_x.x - play_coor.x) + sq(coll_x.y - play_coor.y));
	is_y = sqrt(sq(coll_y.x - play_coor.x) + sq(coll_y.y - play_coor.y));
	return (is_x > is_y ? is_y : is_x);
}
