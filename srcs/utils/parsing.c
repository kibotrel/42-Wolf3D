/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 16:24:06 by kibotrel          #+#    #+#             */
/*   Updated: 2019/04/26 17:35:41 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include "wolf3d.h"

int		row_size(char **coords)
{
	int	y;

	y = 0;
	while (coords[y])
		y++;
	return (y);
}

void	check_row(char *row, t_env *env)
{
	int	i;

	i = 0;
	env->height++;
	if (!*row)
	{
		free_parsemap(row, NULL, env, 1);
		ft_print_error(ERR_EMPTY_ROW, 6);
	}
	while (row[i])
	{
		if (ft_isdigit(row[i]) || row[i] == ' ')
			i++;
		else
		{
			free_parsemap(row, NULL, env, 1);
			ft_print_error(ERR_FORMAT, 7);
		}
	}
}
