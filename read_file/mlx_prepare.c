/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_prepare.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 14:56:55 by vneelix           #+#    #+#             */
/*   Updated: 2019/12/17 17:17:13 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int			mlx_fill(t_figure *f, int line, int color, int endian)
{
	if ((f->mlx.ptr = mlx_init()) == NULL)
		return (-1);
	if ((f->mlx.win = mlx_new_window(f->mlx.ptr, 1366, 768, "FdF")) == NULL)
	{
		free(f->mlx.ptr);
		return (-1);
	}
	if ((f->mlx.img_plot = mlx_new_image(f->mlx.ptr, 1366, 768)) == NULL)
	{
		mlx_destroy_window(f->mlx.ptr, f->mlx.win);
		free(f->mlx.ptr);
		return (-1);
	}
	if ((f->mlx.plot = mlx_get_data_addr(
		f->mlx.img_plot, &color, &line, &endian)) == NULL)
	{
		mlx_destroy_image(f->mlx.ptr, f->mlx.win);
		mlx_destroy_window(f->mlx.ptr, f->mlx.win);
		free(f->mlx.ptr);
		return (-1);
	}
	return (0);
}

int					mlx_prepare(t_figure *f)
{
	return (mlx_fill(f, 1366, 32, 0));
}
