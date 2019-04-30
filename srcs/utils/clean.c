/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:50:58 by kibotrel          #+#    #+#             */
/*   Updated: 2019/04/30 08:58:35 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <wolf3d.h>

void	free_split(char **coords)
{
	int	y;

	y = 0;
	while (coords[y])
		free(coords[y++]);
	free(coords);
}

void	free_parsemap(char *row, char **coords, t_env *env, int code)
{
	if (code > 1)
		free_split(coords);
	if (code > 0)
		free(row);
	if (code < 3)
		free_switch(env, code);
}

void	free_switch(t_env *env, int code)
{
	int	y;

	y = 0;
	if (code)
	{
		if (env->height > 1)
		{
			while (y < env->height - 1)
				free(env->map[y++]);
			free(env->map);
		}
	}
	free(env);
}
