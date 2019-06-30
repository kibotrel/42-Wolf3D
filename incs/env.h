/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grota <grota@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:23:35 by grota             #+#    #+#             */
/*   Updated: 2019/06/30 16:30:30 by reda-con         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

/*
**	Window parameters macros
*/

# define HEIGHT				1080
# define WIDTH				1920
# define RESIZE				SDL_WINDOW_RESIZABLE

/*
**	Useful macros
*/

# define CELL				64
# define RAYS				1920
# define ARGB				372645892
# define STREAM				1
# define DISTANCE			2000
# define TARGETTEXTURE		0x00000008
# define HITBOX				0.12
# define VSYNC				4

/*
**	Color macros
*/

# define SKY				0xffd09951
# define SKY_HITLER			0xff03224c
# define FLOOR				0xfff942e9
# define FLOOR_HITLER		0xffd8d8d8
# define WALL_ORDER			0xffff6950
# define WALL_ALLIANCE		0xff33c47f
# define WALL_ASSEMBLY		0xffa061d1
# define WALL_FEDERATION	0xff1c4f99

/*
**	Error codes
*/

# define E_TP			"\033[31;1mError:\033[0m Wrong teleporter amount"
# define E_EXE			"\033[31;1mError:\033[0m Wrong running directory."
# define E_MAP			"\033[31;1mError:\033[0m Map isn't surrounded by walls."
# define E_WIN			"\033[31;1mError:\033[0m Can't create SDL window."
# define E_COPY			"\033[31;1mError:\033[0m Can't update SDL renderer"
# define E_OPEN			"\033[31;1mError:\033[0m Can't open file."
# define E_INIT			"\033[31;1mError:\033[0m Can't connect with SDL's API."
# define E_FULL			"\033[31;1mError:\033[0m No spawnable cell in the map."
# define E_CLOSE		"\033[31;1mError:\033[0m Can't close file."
# define E_WIDTH 		"\033[31;1mError:\033[0m Map width uneven on each row."
# define E_SPACE		"\033[31;1mError:\033[0m No free cell near teleporters"	
# define E_SPLIT 		"\033[31;1mError:\033[0m Can't retrieve all points."
# define E_FORMAT		"\033[31;1mError:\033[0m Incorrect map format."
# define E_CURSOR		"\033[31;1mError:\033[0m Can't hide cursor position."
# define E_UPDATE		"\033[31;1mError:\033[0m Can't update SDL texture"
# define E_MALLOC		"\033[31;1mError:\033[0m Can't allocate memory."
# define E_TEXTURE		"\033[31;1mError:\033[0m Can't create SDL texture."
# define E_RENDERER		"\033[31;1mError:\033[0m Can't create SDL renderer."
# define E_FILENAME		"\033[31;1mError:\033[0m Incorrect filename (*.w3d)."
# define E_EMPTY_ROW	"\033[31;1mError:\033[0m Empty row within the map."
# define E_EMPTY_FILE	"\033[31;1mError:\033[0m Empty file."

#endif
