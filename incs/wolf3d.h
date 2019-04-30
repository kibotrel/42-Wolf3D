/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grota <grota@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:03:46 by grota             #+#    #+#             */
/*   Updated: 2019/04/30 11:12:43 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

typedef struct	s_env
{
	int			**map;
	int			height;
	int			width;
}				t_env;

/*
**	usage/usage.c
*/

void			usage(void);

/*
**	parsing/map.c
*/

void			parse_file(char *file, t_env *env);

/*
**	utils/clean.c
*/

void			free_split(char **coords);
void			free_switch(t_env *env, int code);
void			free_parsemap(char *row, char **coords, t_env *env, int code);

/*
**	utils/parsing.c
*/

int				row_size(char **coords);
void			check_row(char *row, t_env *env);

#endif
