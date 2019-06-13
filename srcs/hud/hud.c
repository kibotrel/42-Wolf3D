/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 17:07:35 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/13 10:38:03 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include "wolf3d.h"

void	negative(unsigned int *pixel)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned int	color;

	color = *pixel;
	r = (color & 0xff0000) >> 16;
	g = (color & 0xff00) >> 8;
	b = (color & 0xff);
	color = 0xff << 24 | (r ^ 0xff) << 16 | (g ^ 0xff) << 8 | (b ^ 0xff);
	*pixel = color;
}

void	crosshair(t_sdl *sdl)
{
	int	x;
	int	y;

	y = HEIGHT / 2 - 21;
	while (++y < HEIGHT / 2 + 21)
	{
		x = WIDTH / 2 - 2;
		while (++x < WIDTH / 2 + 2)
			negative(&sdl->pixels[x + y * WIDTH]);
	}
	y = HEIGHT / 2 - 2;
	while (++y < HEIGHT / 2 + 2)
	{
		x = WIDTH / 2 - 21;
		while (++x < WIDTH / 2 + 21)
			if (x < WIDTH / 2 - 1 || x > WIDTH / 2 + 1)
				negative(&sdl->pixels[x + y * WIDTH]);
	}
}

void	hud(t_env *env)
{
	minimap(env);
	crosshair(&env->sdl);
}
