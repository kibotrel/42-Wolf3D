/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 14:57:54 by kibotrel          #+#    #+#             */
/*   Updated: 2019/05/29 04:56:18 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "env.h"
#include "wolf3d.h"

int	main(int ac, char **av)
{
	int		loop;
	t_env	*env;

	loop = 1;
	if (ac == 2)
	{
		if (ft_strcmp(av[0], "./wolf3d"))
			ft_print_error(ERR_EXE, 1);
		if (!(env = (t_env*)malloc(sizeof(t_env))))
			ft_print_error(ERR_MALLOC, 5);
		parse_file(av[1], env);
		setup(env);
		raycast(env, &env->sdl, &env->ray);
		while (loop)
			hooks(env, &loop, env->inputs);
		free_sdl(env, 6, NULL, 0);
	}
	else
		usage();
	return (0);
}
