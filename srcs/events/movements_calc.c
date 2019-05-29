/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_calc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 07:57:17 by nde-jesu          #+#    #+#             */
/*   Updated: 2019/05/29 08:11:25 by nde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "wolf3d.h"
#include "env.h"

void			move_forward(t_env *env)
{
		env->cam.coord.x += cos(env->cam.angle) * (10 * env->cam.sprint);
		env->cam.coord.y -= sin(env->cam.angle) * (10 * env->cam.sprint);
}

void			move_backward(t_env *env)
{
		env->cam.coord.x -= cos(env->cam.angle) * (10 * env->cam.sprint);
		env->cam.coord.y += sin(env->cam.angle) * (10 * env->cam.sprint);
}

void			move_left(t_env *env)
{
		env->cam.coord.x += cos(env->cam.angle + R_N) * (8 * env->cam.sprint);
		env->cam.coord.y -= sin(env->cam.angle + R_N) * (8 * env->cam.sprint);
}

void			move_right(t_env *env)
{
		env->cam.coord.x -= cos(env->cam.angle + R_N) * (8 * env->cam.sprint);
		env->cam.coord.y += sin(env->cam.angle + R_N) * (8 * env->cam.sprint);
}
