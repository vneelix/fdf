/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 13:51:24 by vneelix           #+#    #+#             */
/*   Updated: 2019/12/17 17:16:48 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_scaling(t_figure *f, int fg)
{
	if (fg)
	{
		f->delta.a += 1;
		f->delta.b += 1;
	}
	else
	{
		if (f->delta.a == 1 || f->delta.b == 1)
			return ;
		f->delta.a -= 1;
		f->delta.b -= 1;
	}
	f->center = *(f->src + (f->size_x
		/ 2) + f->size_x * (f->size_y / 2));
	f->delta.mov_x += fg ? -(f->center.x) : f->center.x;
	f->delta.mov_y += fg ? -(f->center.y) : f->center.y;
}

static void	key_press2(SDL_Keycode keycode, t_figure *f)
{
	if (keycode == SDLK_LEFT)
		f->delta.mov_x -= 5;
	else if (keycode == SDLK_RIGHT)
		f->delta.mov_x += 5;
	else if (keycode == SDLK_UP)
		f->delta.mov_y -= 5;
	else if (keycode == SDLK_DOWN)
		f->delta.mov_y += 5;
}

void		fdf_init(t_figure *f)
{
	transform_manager(f);
	draw(f);
}

int			key_press(SDL_Keycode keycode, t_figure *f)
{
	if (keycode == SDLK_ESCAPE)
		ft_exit(f);
	else if (keycode == SDLK_SPACE)
		f->p_type = (f->p_type == 'c') ? 'p' : 'c';
	else if (keycode == SDLK_RSHIFT)
		f->delta.c += 1;
	else if (keycode == SDLK_RCTRL)
		f->delta.c -= 1;
	else if (keycode == SDLK_KP_MINUS
			|| keycode == SDLK_KP_PLUS)
		ft_scaling(f, (keycode == SDLK_KP_PLUS ? 1 : 0));
	else if (keycode == SDLK_RETURN)
		delta_init(f);
	else
		key_press2(keycode, f);
	fdf_init(f);
	return (0);
}
