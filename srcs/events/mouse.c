/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 15:37:54 by kibotrel          #+#    #+#             */
/*   Updated: 2019/07/10 15:38:53 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "wolf3d.h"

void	enable_mouse(t_mouse *mouse)
{
	mouse->old_time = mouse->curr_time;
	mouse->toggle_mouse *= -1;
	if (mouse->toggle_mouse == 1)
		SDL_ShowCursor(SDL_DISABLE);
	else
		SDL_ShowCursor(SDL_ENABLE);
}
