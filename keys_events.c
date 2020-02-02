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

static void	ft_exiting(t_figure *f)
{
	mlx_destroy_image(f->mlx.ptr, f->mlx.img_plot);
	mlx_destroy_window(f->mlx.ptr, f->mlx.win);
	free(f->mlx.ptr);
	free(f->src);
	free(f->spc);
	free(f->plt);
	free(f);
	exit(0);
}

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

static void	key_press2(int keycode, void *p)
{
	if (keycode == 123)
		((t_figure*)p)->delta.mov_x -= 5;
	else if (keycode == 124)
		((t_figure*)p)->delta.mov_x += 5;
	else if (keycode == 126)
		((t_figure*)p)->delta.mov_y -= 5;
	else if (keycode == 125)
		((t_figure*)p)->delta.mov_y += 5;
	else if (keycode == 91)
		((t_figure*)p)->delta.x += 1;
	else if (keycode == 84)
		((t_figure*)p)->delta.x -= 1;
	else if (keycode == 88)
		((t_figure*)p)->delta.y -= 1;
	else if (keycode == 86)
		((t_figure*)p)->delta.y += 1;
	else if (keycode == 92)
		((t_figure*)p)->delta.z += 1;
	else if (keycode == 89)
		((t_figure*)p)->delta.z -= 1;
}

void		fdf_init(t_figure *f)
{
	mlx_clear_window(f->mlx.ptr, f->mlx.win);
	transform_manager(f);
	draw(f);
}

int			key_press(int keycode, void *p)
{
	if (keycode == 53)
		ft_exiting(p);
	else if (keycode == 49)
		((t_figure*)p)->p_type = (((t_figure*)p)->p_type == 'c') ? 'p' : 'c';
	else if (keycode == 116)
		((t_figure*)p)->delta.c += 1;
	else if (keycode == 121)
		((t_figure*)p)->delta.c -= 1;
	else if (keycode == 69 || keycode == 78)
		ft_scaling(p, (keycode == 69 ? 1 : 0));
	else if (keycode == 36)
		delta_init(p);
	else
		key_press2(keycode, p);
	fdf_init(p);
	return (0);
}
