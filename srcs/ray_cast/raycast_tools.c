/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 13:14:59 by reda-con          #+#    #+#             */
/*   Updated: 2019/05/09 10:43:42 by reda-con         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "wolf3d.h"
#include <math.h>

void	fun_exit(SDL_Renderer *ren, SDL_Window *win)
{
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	exit(0);
}

double	double_abs(double i)
{
	return ((i > 0) ? i : -i);
}

void	draw_line(t_ptd a, t_ptd b, SDL_Renderer *ren)
{
	t_ptd	delta;
	t_ptd	sign;
	t_ptd	curr;
	int		tab[2];

	delta.x = double_abs((int)b.x - (int)a.x);
	delta.y = double_abs((int)b.y - (int)a.y);
	sign.x = (int)a.x < (int)b.x ? 1 : -1;
	sign.y = (int)a.y < (int)b.y ? 1 : -1;
	tab[0] = (int)delta.x - (int)delta.y;
	curr = a;
	while ((int)curr.x != (int)b.x || (int)curr.y != (int)b.y)
	{
		SDL_RenderDrawPoint(ren, (int)curr.x, (int)curr.y);
		if ((tab[1] = tab[0] * 2) > (int)-delta.y)
		{
			tab[0] -= (int)delta.y;
			curr.x += (int)sign.x;
		}
		if (tab[1] < (int)delta.x)
		{
			tab[0] += (int)delta.x;
			curr.y += (int)sign.y;
		}
	}
}

double	rad_angle(double angle)
{
	return (angle * M_PI / 180);
}

double	my_tan(double angle)
{
	return (sin(angle) / cos(angle));
}
