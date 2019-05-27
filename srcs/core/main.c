/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 14:57:54 by kibotrel          #+#    #+#             */
/*   Updated: 2019/05/27 16:25:41 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "env.h"
#include "wolf3d.h"

// PENSER A PROTECT LE MOVE DU BINAIRE !!!

int	main(int ac, char **av)
{
	int		loop;
	t_env	*env;
	char	*key;

	loop = 1;
	key = ft_strnew(SDL_NUM_SCANCODES);
	if (ac == 2)
	{
		if (ft_strcmp(av[0], "./wolf3d"))
			ft_print_error(ERR_EXE, 1);
		if (!(env = (t_env*)malloc(sizeof(t_env))))
			ft_print_error(ERR_MALLOC, 5);
		parse_file(av[1], env);
		setup(env);
		raycast(env);
		while (loop)
			hooks(env, &loop, key);
		fun_exit(env->sdl.render, env->sdl.win);
	}
	else
		usage();
	return (0);
}
