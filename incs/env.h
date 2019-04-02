/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grota <grota@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:23:35 by grota             #+#    #+#             */
/*   Updated: 2019/04/02 16:19:13 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

/*
**	Window parameters
*/

# define WIN_WIDTH	1920
# define WIN_HEIGHT	1080

/*
**	Basic colors
*/

# define BLACK		0x000000
# define WHITE		0xFFFFFF
# define RED		0xFF0000
# define GREEN		0x00FF00
# define BLUE		0x0000FF
# define MAGENTA	0xFF00FF
# define YELLOW		0xFFFF00
# define CYAN		0x00FFFF

/*
**	Error codes
*/

# define ERR_EXE	"\033[31;1mError:\033[0m Wrong running directory."
#endif
