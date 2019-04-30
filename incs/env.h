/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grota <grota@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:23:35 by grota             #+#    #+#             */
/*   Updated: 2019/04/26 16:33:04 by kibotrel         ###   ########.fr       */
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

# define RED		0xFF0000
# define BLUE		0x0000FF
# define CYAN		0x00FFFF
# define BLACK		0x000000
# define GREEN		0x00FF00
# define WHITE		0xFFFFFF
# define YELLOW		0xFFFF00
# define MAGENTA	0xFF00FF

/*
**	Error codes
*/

# define ERR_EXE		"\033[31;1mError:\033[0m Wrong running directory."
# define ERR_OPEN		"\033[31;1mError:\033[0m Can't open file."
# define ERR_CLOSE		"\033[31;1mError:\033[0m Can't close file."
# define ERR_WIDTH 		"\033[31;1mError :\033[0m Map width uneven on each row."
# define ERR_SPLIT 		"\033[31;1mError :\033[0m Can't retrieve all points."
# define ERR_FORMAT		"\033[31;1mError:\033[0m Incorrect map format."
# define ERR_MALLOC		"\033[31;1mError:\033[0m Can't allocate memory."
# define ERR_FILENAME	"\033[31;1mError:\033[0m Incorrect filename."
# define ERR_EMPTY_ROW	"\033[31;1mError:\033[0m Empty row within the map."
# define ERR_EMPTY_FILE	"\033[31;1mError:\033[0m Empty file."

#endif
