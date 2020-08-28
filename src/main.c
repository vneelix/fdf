/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 21:12:23 by vneelix           #+#    #+#             */
/*   Updated: 2019/12/17 16:27:40 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_exit(t_figure *f)
{
	if (f->sdl.win)
		SDL_DestroyWindow(f->sdl.win);
	if (f->src)
		free(f->src);
	if (f->spc)
		free(f->spc);
	if (f->plt)
		free(f->plt);
	if (f)
		free(f);
	SDL_Quit();
	exit(0);
}

int		SDL_Initialization(t_sdl *sdl, uint32_t w, uint32_t h) {
	if (!sdl || !w || !h)
		return (-1);
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
		return (-1);
	if (!(sdl->win = SDL_CreateWindow("fdf",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN))) {
		SDL_Quit();
		return (-1);
	}
	if (!(sdl->srf = SDL_GetWindowSurface(sdl->win))) {
		SDL_DestroyWindow(sdl->win);
		SDL_Quit();
		return (-1);
	}
	return (0);
}

void	window(t_figure *f)
{
	fdf_init(f);
	SDL_Loop(f);
}

int		main(int argc, char **argv)
{
	int			fd;
	t_figure	*f;

	if (argc != 2)
	{
		if (write(2, "usage: fdf file\n", 16) < 0)
			return (-1);
		return (0);
	}
	if ((fd = open(argv[1], O_RDONLY)) == (-1))
	{
		if (write(2, "unable to read file\n", 20) < 0)
			return (-1);
		return (-1);
	}
	if ((f = ft_getp(fd)) == NULL)
	{
		close(fd);
		if (write(2, "incorrect file\n", 15) < 0)
			return (-1);
		return (-1);
	}
	if (SDL_Initialization(&f->sdl, 1366, 768) < 0)
		ft_exit(f);
	close(fd);
	window(f);
	return (0);
}
