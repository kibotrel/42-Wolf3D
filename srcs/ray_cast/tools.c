/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reda-con <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 13:14:59 by reda-con          #+#    #+#             */
/*   Updated: 2019/04/26 13:19:22 by reda-con         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"

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

void	check_wall_color(SDL_Renderer *ren, int wall, int wall_side)
{
	int		darker;

	darker = 1;
	if (wall_side == 1)
		darker = 2;
	if (wall == 0)
		SDL_SetRenderDrawColor(ren, 255 / darker, 0 / darker, 0 / darker, 255);
	else if (wall == 1)
		SDL_SetRenderDrawColor(ren, 0 / darker, 255 / darker, 0 / darker, 255);
	else if (wall == 2)
		SDL_SetRenderDrawColor(ren, 0 / darker, 0 / darker, 255 / darker, 255);
	else if (wall == 3)
		SDL_SetRenderDrawColor(ren, 255 / darker, 255 / darker,\
				0 / darker, 255);
	else if (wall == 4)
		SDL_SetRenderDrawColor(ren, 255 / darker, 0 / darker,\
				255 / darker, 255);
}
