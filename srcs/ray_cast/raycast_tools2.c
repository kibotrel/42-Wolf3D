/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_tools2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 11:01:01 by reda-con          #+#    #+#             */
/*   Updated: 2019/05/10 11:24:55 by nde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

double	sq(double n)
{
	return (pow(n, 2));
}

double	length(t_ptd coll_x, t_ptd coll_y, t_ptd play_coor)
{
	double	is_y;
	double	is_x;

	is_x = sqrt(sq(coll_x.x - play_coor.x) + sq(coll_x.y - play_coor.y));
	is_y = sqrt(sq(coll_y.x - play_coor.x) + sq(coll_y.y - play_coor.y));
	if (is_x > is_y)
		return (is_y);
	else
		return (is_x);
}
