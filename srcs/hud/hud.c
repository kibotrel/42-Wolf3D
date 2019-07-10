/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 17:07:35 by kibotrel          #+#    #+#             */
/*   Updated: 2019/07/10 15:18:10 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include "wolf3d.h"


void		display_time(unsigned int time)
{
	double	sec;

	ft_putstr("\ne");
	ft_putendl("\033[33mGOOD JOB, YOU WON !\33[0m");
	ft_putstr("\033[1;31mYour time is : \033[0m\033[35m");
	sec = time / 1000;
	if (sec > 60)
	{
		ft_putnbr(sec / 60);
		sec = fmod(sec, 60);
		ft_putchar('\'');
	}
	ft_putnbr(sec);
	ft_putchar('\"');
	ft_putnbr(fmod(time, 1000));
	ft_putstr("\n");
	ft_putstr("\033[0m");
}

static void	negative(unsigned int *pixel)
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

void		crosshair(t_sdl *sdl, t_env *env)
{
	int	x;
	int	y;

	y = env->h / 2 - 21;
	while (++y < env->h / 2 + 21)
	{
		x = env->w / 2 - 2;
		while (++x < env->w / 2 + 2)
			negative(&sdl->pixels[x + y * env->w]);
	}
	y = env->h / 2 - 2;
	while (++y < env->h / 2 + 2)
	{
		x = env->w / 2 - 21;
		while (++x < env->w / 2 + 21)
			if (x < env->w / 2 - 1 || x > env->w / 2 + 1)
				negative(&sdl->pixels[x + y * env->w]);
	}
}
