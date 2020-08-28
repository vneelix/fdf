/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot_gen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 14:36:21 by vneelix           #+#    #+#             */
/*   Updated: 2019/12/20 13:03:04 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		ft_parallel(t_figure *f)
{
	size_t			i;
	size_t			count;

	i = 0;
	count = f->size_x * f->size_y;
	while (i < count)
	{
		*(f->plt + i) = *(f->spc + i);
		i += 1;
	}
}

void		ft_central(t_figure *f)
{
	size_t			i;
	double			x;
	double			y;
	double			z;

	i = 0;
	while (i < f->size_x * f->size_y)
	{
		x = (f->spc + i)->x;
		y = (f->spc + i)->y;
		z = (f->spc + i)->z;
		if ((int)(f->view_point.z - z) <= 0)
		{
			(f->plt + (i++))->color = (-1);
			continue ;
		}
		else
			(f->plt + i)->color = (f->spc + i)->color;
		(f->plt + i)->x = ((0 - z) * (f->view_point.x
			- x) / (f->view_point.z - z)) + x;
		(f->plt + i)->y = ((0 - z) * (f->view_point.y
			- y) / (f->view_point.z - z)) + y;
		(f->plt + i)->color = (f->spc + i)->color;
		i += 1;
	}
}
