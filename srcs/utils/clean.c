/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:50:58 by kibotrel          #+#    #+#             */
/*   Updated: 2019/05/28 23:28:18 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <wolf3d.h>

int		free_parse(char *row, char **coords, t_env *env, int code)
{
	if (code > 1)
		free_split(coords);
	if (code > 0)
		free(row);
	if (code < 3)
		free_switch(env, code);
	return (1);
}

int		free_switch(t_env *env, int code)
{
	int	y;

	if (!(y = 0) && code)
	{
		if (env->height > 1)
		{
			while (y < env->height - 1)
				free(env->map[y++]);
			free(env->map);
		}
	}
	free(env);
	return (1);
}

void	free_split(char **coords)
{
	int	y;

	y = 0;
	while (coords[y])
		free(coords[y++]);
	free(coords);
}

void		free_sdl(SDL_Renderer *ren, SDL_Window *win)
{
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
}
