/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_tools2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reda-con <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 11:01:01 by reda-con          #+#    #+#             */
/*   Updated: 2019/05/09 11:37:58 by reda-con         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

double	sq(double n)
{
	return (pow(n, 2));
}

double	length(t_ptd coll_x, t_ptd coll_y, t_ptd play_coor)
{
	double	ret;

	ret = (sqrt(sq(coll_x.x - play_coor.x) + sq(coll_x.y - play_coor.y))\
			> sqrt(sq(coll_y.x - play_coor.x) + sq(coll_y.y - play_coor.y)))\
		? sqrt(sq(coll_y.x - play_coor.x) + sq(coll_y.y - play_coor.y))\
		: sqrt(sq(coll_x.x - play_coor.x) + sq(coll_x.y - play_coor.y));
	return (ret);
}
