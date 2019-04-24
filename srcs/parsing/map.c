/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 15:16:20 by kibotrel          #+#    #+#             */
/*   Updated: 2019/04/24 17:24:14 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "env.h"
#include "wolf3d.h"

static void	expand_map(int **map, t_env *env)
{
	int		y;
	int		x;

	y = -1;
	while (++y < env->height - 1)
	{
		x = -1;
		while (++x < env->width)
			map[y][x] = env->grid[y][x];
		free(env->grid[y]);
	}
	free(env->grid);
}

static void array_to_map(char **coords, t_env *env)
{
	int		y;
	int		x;
	int		**map

	if (!(map = (int**)malloc(sizeof(int*) * env->height)))
		print_error("ERR_MALLOC", 5); // Need to free ? there
	y = -1;
	while (++y < env->height)
		if (!(map[y] = (int*)malloc(sizeof(int) * (env->width))))
			print_error("ERR_MALLOC", 5); // Need to free ? there
	if (env->height - 1 > 0)
		expand_map(map, env);
	x = -1;
	while (++x < env->width)
		map[y - 1][x] = ft_atoi(coords[x]);
	env->map = map;
}

static void	check_row(char *row)
{
	int		i;

	i = 0;
	if (!*row)
		print_error(ERR_EMPTY_ROW, 6); // Need to free ? there
	while (row[i])
	{
		if (ft_isdigit(row[i]) || row[i] == ' ')
			i++;
		else
			print_error(ERR_FORMAT, 7); // Need to free ? there
	}
}

static void	build_map(const int fd, t_env *env)
{
	char	*row;
	char	**coords;

	env->height = 0;
	while (ft_get_next_line(fd, &row))
	{
		env->height++;
		check_row(row);
		if (!(coords = ft_strsplit(row, ' '))) // Need to secure strsplit
			print_error(ERR_SPLIT, 8); // Need to free ? there
		if (env->height == 1)
			env->width = row_size(coords);
		else if (row_size(coords) != env->width)
			print_error(ERR_WIDTH, 9); // Need to free ? there
		array_to_map(coords, env);
		free(row);
		free_split(coords);
	}
	if (!env->height)
		print_error(ERR_EMPTY_FILE, 10); // Need to free there
}

void		parse_file(char *file, t_env *env)
{
	int	fd;

	if (!ft_isvalidname(file, ".w3d"))
		ft_print_error(ERR_FILENAME, 2); // Need to free env there
	if ((fd = open(file, O_RDONLY)) < 0)
		ft_print_error(ERR_OPEN, 3); // Need to free env there
	build_map(fd, env);
	if (close(fd))
		ft_print_error(ERR_CLOSE, 4); // Need to free ? there
}
