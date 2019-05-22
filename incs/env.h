/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grota <grota@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:23:35 by grota             #+#    #+#             */
/*   Updated: 2019/05/22 17:09:08 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <math.h>

/*
**	Window parameters macros
*/

# define WIDTH			1920
# define HEIGHT			1080

/*
**	Maths macros
*/

# define R_E			0
# define R_N			M_PI_2
# define R_W			M_PI
# define R_S			3 * M_PI_2 // to change l8er

/*
**	Useful macros
*/

# define CELL			64
# define HEIGHT_CAM		200
# define RESIZE			0x00000200
# define RGBA			373694468
# define RESIZE			0x00000200
# define S_UINT			4
# define STREAM			1
/*
**	Color macros
*/

# define DARK_GRAY		0x575757ff

/*
**	Error codes
*/

# define ERR_EXE		"\033[31;1mError:\033[0m Wrong running directory."
# define ERR_MAP		"\033[31;1mError:\033[0m Map isn't surrounded by walls."
# define ERR_OPEN		"\033[31;1mError:\033[0m Can't open file."
# define ERR_CLOSE		"\033[31;1mError:\033[0m Can't close file."
# define ERR_WIDTH 		"\033[31;1mError:\033[0m Map width uneven on each row."
# define ERR_SPLIT 		"\033[31;1mError:\033[0m Can't retrieve all points."
# define ERR_FORMAT		"\033[31;1mError:\033[0m Incorrect map format."
# define ERR_MALLOC		"\033[31;1mError:\033[0m Can't allocate memory."
# define ERR_FILENAME	"\033[31;1mError:\033[0m Incorrect filename (*.w3d)."
# define ERR_EMPTY_ROW	"\033[31;1mError:\033[0m Empty row within the map."
# define ERR_EMPTY_FILE	"\033[31;1mError:\033[0m Empty file."

#endif
