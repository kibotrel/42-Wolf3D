/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grota <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 11:44:29 by grota             #+#    #+#             */
/*   Updated: 2018/03/15 16:17:40 by grota            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static int			ft_tabzero(int **tab, t_point2i size)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	if (!tab)
		return (0);
	while (i < size.y)
	{
		while (j < size.x)
			tab[i][j++] = 0;
		i++;
		j = 0;
	}
	return (1);
}

t_point2i			ft_tabsize(char **argv, char **line)
{
	t_point2i	size;
	char		**split;
	int			i;
	int			fd;

	size = (t_point2i){0, 0};
	i = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		ft_error_exit("./fdf: Invalid file");
	while (get_next_line(fd, line))
	{
		size.y++;
		split = ft_strsplit(*line, ' ');
		while (split[i])
			free(split[i++]);
		free(split);
		if (i > size.x)
			size.x = i;
		i = 0;
	}
	close(fd);
	return (size);
}

static int			**ft_create_tab(t_point2i size)
{
	int			i;
	int			**tab;

	i = 0;
	if (!(tab = (int **)malloc(sizeof(int *) * size.y)))
		return (NULL);
	while (i < size.y)
		if (!(tab[i++] = (int *)malloc(sizeof(int) * size.x)))
			return (NULL);
	ft_tabzero(tab, size);
	return (tab);
}

static t_shape3d	ft_tabto3dshape(t_tab tab)
{
	t_shape3d	shape;
	int			i;
	int			j;
	int			k;

	shape.size = tab.size;
	shape.nb_pts = tab.size.x * tab.size.y;
	shape.point = (t_point3d *)malloc(sizeof(t_point3d) * shape.nb_pts);
	i = 0;
	j = 0;
	k = 0;
	while (j < tab.size.y)
	{
		while (i < tab.size.x)
		{
			(shape.point[k]).x = (double)i;
			(shape.point[k]).y = (double)j;
			(shape.point[k++]).z = (double)tab.tab[j][i++];
		}
		i = 0;
		j++;
	}
	return (shape);
}

t_shape3d			ft_fileto3dshape(char **argv)
{
	char		*line;
	char		**split;
	t_tab		tab;
	t_point2i	coord;
	int			fd;

	line = ft_strnew(1);
	coord = (t_point2i){0, 0};
	tab.size = ft_tabsize(argv, &line);
	tab.tab = ft_create_tab(tab.size);
	fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		split = ft_strsplit(line, ' ');
		while (split[coord.y])
		{
			tab.tab[coord.x][coord.y] = ft_atoi(split[coord.y]);
			free(split[coord.y++]);
		}
		free(split);
		coord = (t_point2i){coord.x + 1, 0};
	}
	free(line);
	return (ft_tabto3dshape(tab));
}
