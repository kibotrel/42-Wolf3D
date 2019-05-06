/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grota <grota@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:03:46 by grota             #+#    #+#             */
/*   Updated: 2019/05/06 17:45:00 by kibotrel         ###   ########.fr       */
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

int			free_switch(t_env *env, int code);
int			free_parse(char *row, char **coords, t_env *env, int code);
void		free_split(char **coords);

/*
**	utils/parsing.c
*/

int				size(char **coords);
void			bottom_border(t_env *env);
void			check_row(char *row, t_env *env);
void			limits(char *row, char **coords, t_env *env);

#endif
