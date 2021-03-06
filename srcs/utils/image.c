/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reda-con <reda-con@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 11:33:37 by reda-con          #+#    #+#             */
/*   Updated: 2019/06/27 09:45:56 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "wolf3d.h"
#include "env.h"

void	upload_image(t_env *env, int i)
{
	raycast(env, &env->ray);
	crosshair(&env->sdl, env);
	if (i == 1 && env->h > HEIGHT / 2 && env->w > WIDTH / 2)
		minimap(env);
	if (SDL_UpdateTexture(env->sdl.text, 0, env->sdl.pixels, env->w * 4) < 0)
		free_sdl(env, 5, E_UPDATE, 17);
	if (SDL_RenderCopy(env->sdl.ren, env->sdl.text, 0, 0) < 0)
		free_sdl(env, 5, E_COPY, 18);
	SDL_RenderPresent(env->sdl.ren);
}
