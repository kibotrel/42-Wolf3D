/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 14:57:54 by kibotrel          #+#    #+#             */
/*   Updated: 2019/05/09 17:23:55 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "env.h"
#include "wolf3d.h"

#include <stdio.h>//


// PENSER A PROTECT LE MOVE DU BINAIRE !!!
int	main(int ac, char **av)
{
	t_env	*env;

	int x, y;//
	y = -1;//

	if (ac == 2)
	{
		if (ft_strcmp(av[0], "./wolf3d"))
			ft_print_error(ERR_EXE, 1);
		if (!(env = (t_env*)malloc(sizeof(t_env))))
			ft_print_error(ERR_MALLOC, 5);
		parse_file(av[1], env);
		while (++y < env->height)//
		{//
			x = -1;//
			while (++x < env->width)//
				printf("%d ", env->map[y][x]);//
			printf("\n");//
		}//
	}
	else
		usage();
	return (0);
}
