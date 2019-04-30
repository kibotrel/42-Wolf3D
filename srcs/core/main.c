/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 14:57:54 by kibotrel          #+#    #+#             */
/*   Updated: 2019/04/30 11:13:40 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "env.h"
#include "wolf3d.h"

int	main(int ac, char **av)
{
	t_env	*env;

	if (ac == 2)
	{
		if (ft_strcmp(av[0], "./wolf3d"))
			ft_print_error(ERR_EXE, 1);
		if (!(env = (t_env*)malloc(sizeof(t_env))))
			ft_print_error(ERR_MALLOC, 5);
		parse_file(av[1], env);
	}
	else
		usage();
	return (0);
}
