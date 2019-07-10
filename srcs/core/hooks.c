/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 18:02:39 by kibotrel          #+#    #+#             */
/*   Updated: 2019/07/10 14:03:59 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "libft.h"
#include "env.h"
#include "wolf3d.h"


void	hooks(t_env *env, t_pos *flags, char *key, t_mouse *mouse)
{
	mouse->curr_time = SDL_GetTicks();
	mouse->cur_frame = SDL_GetTicks();
	trigger_event(key, env, mouse, flags);
	if (key[SDL_SCANCODE_ESCAPE])
		flags->x = 0;
	if (key[SDL_SCANCODE_P] && mouse->curr_time > mouse->old_time + 500)
	{
		enable_mouse(&env->mouse);
		flags->y = 1;
	}
	if (mouse->nb_frame > 0)
	{
		if (mouse->toggle_mouse == 1)
		{
			ft_putstr("\e[1000Dfps: ");
			ft_putnbr(1000 / (mouse->cur_frame - mouse->old_frame));
			ft_putstr("\e[2k");
		}
		mouse->old_frame = mouse->cur_frame;
		mouse->nb_frame = 0;
	}
	++mouse->nb_frame;
	process_event(key, env, mouse, flags);
}
