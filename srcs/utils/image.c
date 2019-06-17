/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reda-con <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 11:33:37 by reda-con          #+#    #+#             */
/*   Updated: 2019/06/03 13:02:39 by reda-con         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "wolf3d.h"
#include "env.h"

void	upload_image(t_env *env, int i)
{
	raycast(env, &env->ray);
	if (i == 1)
		minimap(env);
	if (SDL_UpdateTexture(env->sdl.text, 0, env->sdl.pixels, WIDTH * 4) < 0)
		free_sdl(env, 5, ERR_UPDATE, 17);
	if (SDL_RenderCopy(env->sdl.ren, env->sdl.text, 0, 0) < 0)
		free_sdl(env, 5, ERR_COPY, 18);
	SDL_RenderPresent(env->sdl.ren);
}
