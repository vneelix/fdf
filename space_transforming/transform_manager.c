/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_manager.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 13:21:56 by vneelix           #+#    #+#             */
/*   Updated: 2019/12/12 16:53:39 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		zero_pozition(t_figure *f, t_delta delta, int flag)
{
	if (flag == 0)
	{
		f->delta.mov_x = -(f->center.x);
		f->delta.mov_y = -(f->center.y);
		f->delta.mov_z = -(f->center.z / 2);
	}
	else
	{
		f->delta.mov_x = f->center.x;
		f->delta.mov_y = f->center.y;
		f->delta.mov_z = f->center.z / 2;
	}
	move_f(f);
	f->delta = delta;
}

static void		spc_rotate(t_figure *f)
{
	if (f->delta.x > 360)
		f->delta.x -= 360;
	else if (f->delta.x < -360)
		f->delta.x += 360;
	if (f->delta.y > 360)
		f->delta.y -= 360;
	else if (f->delta.y < -360)
		f->delta.y += 360;
	if (f->delta.z > 360)
		f->delta.z -= 360;
	else if (f->delta.z < -360)
		f->delta.z += 360;
	zero_pozition(f, f->delta, 0);
	if (f->delta.x != 0)
		rotate_x(f);
	if (f->delta.y != 0)
		rotate_y(f);
	if (f->delta.z != 0)
		rotate_z(f);
	zero_pozition(f, f->delta, 1);
}

void			transform_manager(t_figure *f)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = f->size_x * f->size_y;
	while (i < count)
	{
		*(f->spc + i) = *(f->src + i);
		i += 1;
	}
	scale(f);
	f->center = *(f->spc + (f->size_x
		/ 2) + f->size_x * (f->size_y / 2));
	if (f->delta.x != 0 || f->delta.y != 0 || f->delta.z != 0)
		spc_rotate(f);
	move_f(f);
	f->center = *(f->spc + (f->size_x
		/ 2) + f->size_x * (f->size_y / 2));
	if (f->p_type == 'p')
		ft_parallel(f);
	else if (f->p_type == 'c')
		ft_central(f);
}
