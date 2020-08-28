/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_transform.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 12:45:21 by vneelix           #+#    #+#             */
/*   Updated: 2019/12/11 20:12:28 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	scale(t_figure *f)
{
	size_t		i;
	size_t		count;

	i = 0;
	count = f->size_x * f->size_y;
	while (i < count)
	{
		(f->spc + i)->x *= f->delta.a;
		(f->spc + i)->y *= f->delta.b;
		(f->spc + i)->z *= f->delta.c;
		i += 1;
	}
}

void	move_f(t_figure *f)
{
	size_t		i;
	size_t		count;

	i = 0;
	count = f->size_x * f->size_y;
	while (i < count)
	{
		(f->spc + i)->x += f->delta.mov_x;
		(f->spc + i)->y += f->delta.mov_y;
		(f->spc + i)->z += f->delta.mov_z;
		i += 1;
	}
}

void	rotate_x(t_figure *f)
{
	size_t		i;
	size_t		count;
	double		rad;
	double		y;
	double		z;

	i = 0;
	count = f->size_x * f->size_y;
	rad = (double)f->delta.x * (M_PI / (double)180);
	while (i < count)
	{
		y = (f->spc + i)->y;
		z = (f->spc + i)->z;
		(f->spc + i)->y = y * cos(rad) - z * sin(rad);
		(f->spc + i)->z = y * sin(rad) + z * cos(rad);
		i += 1;
	}
}

void	rotate_y(t_figure *f)
{
	size_t		i;
	size_t		count;
	double		rad;
	double		x;
	double		z;

	i = 0;
	count = f->size_x * f->size_y;
	rad = (double)f->delta.y * (M_PI / (double)180);
	while (i < count)
	{
		x = (f->spc + i)->x;
		z = (f->spc + i)->z;
		(f->spc + i)->x = x * cos(rad) - z * sin(rad);
		(f->spc + i)->z = x * sin(rad) + z * cos(rad);
		i += 1;
	}
}

void	rotate_z(t_figure *f)
{
	size_t		i;
	size_t		count;
	double		rad;
	double		x;
	double		y;

	i = 0;
	count = f->size_x * f->size_y;
	rad = (double)f->delta.z * (M_PI / (double)180);
	while (i < count)
	{
		x = (f->spc + i)->x;
		y = (f->spc + i)->y;
		(f->spc + i)->x = x * cos(rad) - y * sin(rad);
		(f->spc + i)->y = x * sin(rad) + y * cos(rad);
		i += 1;
	}
}
