/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drawline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 15:12:31 by vneelix           #+#    #+#             */
/*   Updated: 2019/12/20 12:43:06 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static float	clampf(float value, float min, float max) {
	if (value <= min) {
		return (min);
	}
	else if (value >= max) {
		return (max);
	} else {
		return (value);
	}
}

static void		gradient(t_point *beg, t_point *end, float length,
									t_point *curr, uint32_t *pixel) {
	float	left_part_len = sqrtf(pow(curr->x - beg->x, 2) + pow(curr->y - beg->y, 2));
	float	right_part_len = sqrtf(pow(end->x - curr->x, 2) + pow(end->y - curr->y, 2));

	float	ratio_first_color = left_part_len / length;
	float	ratio_second_color = right_part_len / length;

	uint32_t color = 0;
	color |= (uint32_t)(clampf(
		((beg->color & 255 << 16) >> 16) * ratio_second_color + ((end->color & 255 << 16) >> 16) * ratio_first_color, 0, 255)
	) << 16;
	color |= (uint32_t)(clampf(
		((beg->color & 255 << 8) >> 8) * ratio_second_color + ((end->color & 255 << 8) >> 8) * ratio_first_color, 0, 255)
	) << 8;
	color |= (uint32_t)(clampf(
		(beg->color & 255) * ratio_second_color + (end->color & 255) * ratio_first_color, 0, 255)
	);

	uint32_t index = (int)curr->x + 1366 * ((int)curr->y);
	pixel[index] = color;
}

static void		drawline(t_point p1, t_point p2, t_figure *f)
{
	int		delta[2];
	int		sign[2];
	int		error[2];

	t_point beg = p1, end = p2;
	float	length = sqrtf(pow(end.x - beg.x, 2) + pow(end.y - beg.y, 2));

	delta[0] = abs((int)p2.x - (int)p1.x);
	delta[1] = abs((int)p2.y - (int)p1.y);
	sign[0] = (int)p1.x < (int)p2.x ? 1 : (-1);
	sign[1] = (int)p1.y < (int)p2.y ? 1 : (-1);
	error[0] = delta[0] - delta[1];
	while ((int)p1.x != (int)p2.x || (int)p1.y != (int)p2.y)
	{
		if ((int)p1.x >= 0 && (int)p1.x < 1366
			&& (int)p1.y >= 0 && (int)p1.y < 768) {
			gradient(&beg, &end, length, &p1, f->sdl.srf->pixels);
		}
		error[1] = error[0] * 2;
		if (error[1] > -(delta[1]))
		{
			error[0] -= (delta[1]);
			p1.x = (int)(p1.x) + sign[0];
		}
		if (error[1] < delta[0])
		{
			error[0] += (delta[0]);
			p1.y = (int)(p1.y) + sign[1];
		}
	}
}

void			draw(t_figure *f)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 1366 * 768;
	ft_bzero(f->sdl.srf->pixels, sizeof(uint32_t) * count);
	count = f->size_x * f->size_y;
	while (i < count && count != 1)
	{
		if ((i + 1) % f->size_x != 0 || i == 0)
			drawline(*(f->plt + i), *(f->plt + i + 1), f);
		if (i < (count - f->size_x))
			drawline(*(f->plt + i), *(f->plt + i + f->size_x), f);
		i += 1;
	}
	SDL_UpdateWindowSurface(f->sdl.win);
}
