/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reda-con <reda-con@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 13:14:59 by reda-con          #+#    #+#             */
/*   Updated: 2019/05/10 18:47:39 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "env.h"
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

void	draw_rc(t_ptd a, t_ptd b, SDL_Renderer *ren, int clr)
{
	t_ptd	cur;

	cur.x = a.x;
	cur.y = 0;
	while (cur.y < WIN_HEIGHT)
	{
		if (cur.y < a.y)
			SDL_SetRenderDrawColor(ren, 0, 255, 255, 255);
		else if (cur.y >= a.y && cur.y <= b.y)
			SDL_SetRenderDrawColor(ren, clr >> 16, clr >> 8, clr, 255);
		else
			SDL_SetRenderDrawColor(ren, 200, 200, 200, 255);
		SDL_RenderDrawPoint(ren, (int)cur.x, (int)cur.y);
		++cur.y;
	}
}
