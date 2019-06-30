/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 16:24:06 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/30 17:47:22 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include "wolf3d.h"

int		size(char **coords)
{
	int	y;

	y = 0;
	while (coords[y])
		y++;
	return (y);
}

void	bottom_border(t_env *env)
{
	int		y;
	int		x;

	y = env->height - 1;
	x = -1;
	while (++x < env->width)
		if (env->map[y][x] != 1)
			ft_print_error(E_MAP, 11);
}

void	check_row(char *row, t_env *env)
{
	int		i;

	i = -1;
	env->height++;
	if (!row)
		ft_print_error(E_EMPTY_ROW, 6);
	while (row[++i])
		if (!ft_isdigit(row[i]) && row[i] != ' ')
			ft_print_error(E_FORMAT, 7);
}

void	limits(char **coords, t_env *env)
{
	int		y;
	int		end;
	int		flag;

	y = -1;
	end = size(coords) - 1;
	if (!(flag = 0) && env->height == 1)
	{
		while (coords[++y] && flag != 1)
			if (coords[y][0] != '1' || (coords[y][0] == '1' && coords[y][1]))
				flag = 1;
	}
	else if (coords[0][0] != '1' || (coords[0][0] == '1' && coords[0][1])
		|| coords[end][0] != '1' || (coords[end][0] == '1' && coords[end][1]))
		flag = 1;
	if (flag == 1)
		ft_print_error(E_MAP, 11);
}

int		teleport_space(t_env *env, int i, int walls)
{
	t_pos	pos;

	while (++i < 2 && walls < 4)
	{
		walls = 0;
		pos.x = env->tp_start[i].x;
		pos.y = env->tp_start[i].y;
		if (env->map[(int)pos.y][(int)pos.x + 1] != 1)
			env->tp_end[i] = tp_infos(pos.x + 1, pos.y, 0);
		else
			walls++;
		if (env->map[(int)pos.y - 1][(int)pos.x] != 1)
			env->tp_end[i] = tp_infos(pos.x, pos.y - 1, 90);
		else
			walls++;
		if (env->map[(int)pos.y][(int)pos.x - 1] != 1)
			env->tp_end[i] = tp_infos(pos.x - 1, pos.y, 180);
		else
			walls++;
		if (env->map[(int)pos.y + 1][(int)pos.x] != 1)
			env->tp_end[i] = tp_infos(pos.x, pos.y + 1, 270);
		else
			walls++;
	}
	return (walls < 4);
}
