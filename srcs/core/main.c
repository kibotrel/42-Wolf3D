/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 14:57:54 by kibotrel          #+#    #+#             */
/*   Updated: 2019/04/02 15:45:49 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"

int	main(int ac, char **av)
{
	if (ac == 2 && !ft_strcmp(av[0], "./wolf3d"))
		ft_putendl("Parsing incoming");
	else
		usage();
	return (0);
}
