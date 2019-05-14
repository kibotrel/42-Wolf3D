/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 09:33:34 by nde-jesu          #+#    #+#             */
/*   Updated: 2019/05/14 10:35:05 by nde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"

# define WIDTH 1000
# define HEIGHT 1000


void	put_pixel_tex(uint32_t *tab, int x, int y, int color)
{
	int	pixel;
	
	if (x >= 0 && x <= WIDTH && y >= 0 && y <= HEIGHT)
	{
		pixel = x + (y * WIDTH);
		tab[pixel] = color;
	}
}


int	main(void)
{
	SDL_Event		ev;
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Texture		*tex;
	uint32_t			*pixels;


	pixels = malloc (sizeof(uint32_t) * (WIDTH * HEIGHT));
	// Mettre toutes les valeurs de base a 0 ?
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE, &win, &ren);
	tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
	// Modifier le buffer
	put_pixel_tex(pixels, 100, 100, 0xEAEAEA);
	SDL_UpdateTexture(tex, NULL, pixels, WIDTH * sizeof(uint32_t));
	SDL_RenderCopy(ren, tex, NULL, NULL);
	SDL_RenderPresent(ren);
	while(42)
	{
		SDL_PollEvent(&ev);
		if (ev.window.event == SDL_WINDOWEVENT_CLOSE)
			exit(0);
	}
}