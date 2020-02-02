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

static void		point_prepare(t_point *p1, t_figure *f)
{
	int		index;

	if ((int)p1->x >= 0 && (int)p1->x < 1366
		&& (int)p1->y >= 0 && (int)p1->y < 768)
	{
		index = (int)p1->x + 1366 * ((int)p1->y);
		((uint32_t*)(f->mlx.plot))[index] = p1->color;
	}
}

static void		drawline(t_point p1, t_point p2, t_figure *f)
{
	int		delta[2];
	int		sign[2];
	int		error[2];

	delta[0] = labs((int)p2.x - (int)p1.x);
	delta[1] = labs((int)p2.y - (int)p1.y);
	sign[0] = (int)p1.x < (int)p2.x ? 1 : (-1);
	sign[1] = (int)p1.y < (int)p2.y ? 1 : (-1);
	error[0] = delta[0] - delta[1];
	while ((int)p1.x != (int)p2.x || (int)p1.y != (int)p2.y)
	{
		point_prepare(&p1, f);
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
	while (i < count)
		((uint32_t*)f->mlx.plot)[i++] = 0;
	i = 0;
	count = f->size_x * f->size_y;
	while (i < count && count != 1)
	{
		if ((i + 1) % f->size_x != 0 || i == 0)
			if ((f->plt + i)->color != (-1)
				&& (f->plt + i + 1)->color != (-1))
				drawline(*(f->plt + i), *(f->plt + i + 1), f);
		if (i < (count - f->size_x))
			if ((f->plt + i)->color != (-1)
				&& (f->plt + i + f->size_x)->color != (-1))
				drawline(*(f->plt + i), *(f->plt + i + f->size_x), f);
		i += 1;
	}
	point_prepare((f->plt + count - 1), f);
	mlx_put_image_to_window(f->mlx.ptr,
		f->mlx.win, f->mlx.img_plot, 0, 0);
}
