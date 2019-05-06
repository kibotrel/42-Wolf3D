/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:30:44 by kibotrel          #+#    #+#             */
/*   Updated: 2019/05/06 18:55:05 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	file_format(void)
{
	ft_putendl("\n\033[0m\033[32;1mFile format:\033[0m\033[36m");
	ft_putendl("\n\tW.I.P\n");
}

static void	error_handling(void)
{
	ft_putendl("\033[0m\033[32;1mError handling:\033[0;36m");
	ft_putendl("\n\tEach following error code are handled by the program");
	ft_putendl("\n\tW.I.P");
	ft_putendl("\n\tUse \"echo $?\" to know the last process returned value");
}

static void	keyboard_controls(void)
{
	ft_putendl("\n\033[0m\033[32;1mKeyboard controls:\033[0;36m");
	ft_putendl("\n\tThe following inputs are handled in window");
	ft_putendl("\n\tW.I.P");
}

static void	mouse_controls(void)
{
	ft_putendl("\n\033[0m\033[32;1mMouse controls:\033[0;36m");
	ft_putendl("\n\tThe following inputs are handled in window");
	ft_putendl("\n\tW.I.P");
}

void		usage(void)
{
	ft_putendl("\n\033[32;1musage: ./wolf3d \'map.w3d\'\033[0;36m");
	ft_putendl("\n\tmap.w3d : array of values");
	file_format();
	error_handling();
	keyboard_controls();
	mouse_controls();
	ft_putendl("\n\t\t\t\t\t\t\033[0m\033[32;1mMade by ???\n\033[0m");
}
