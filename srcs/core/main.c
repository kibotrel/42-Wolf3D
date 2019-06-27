/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 14:57:54 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/27 09:39:59 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "env.h"
#include "wolf3d.h"

int	main(int ac, char **av)
{
	t_pos	flags;
	t_env	*env;
	int		i;

	flags.x = 1;
	i = 0;
	if (ac == 2)
	{
		if (ft_strcmp(av[0], "./wolf3d"))
			ft_print_error(E_EXE, 1);
		if (!(env = (t_env*)malloc(sizeof(t_env))))
			ft_print_error(E_MALLOC, 5);
		parse_file(av[1], env);
		set_env(env);
		raycast(env, &env->ray);
		while (flags.x)
			hooks(env, &flags, env->inputs, &env->mouse);
		free_sdl(env, 6, NULL, 0);
	}
	else
		usage();
	return (0);
}
