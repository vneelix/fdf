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

void			window(t_figure *f)
{
	fdf_init(f);
	mlx_hook(f->mlx.win, 2, 0, key_press, f);
	mlx_loop(f->mlx.ptr);
}

int				main(int argc, char **argv)
{
	int			fd;
	t_figure	*f;

	if (argc != 2)
	{
		write(2, "usage: fdf file\n", 16);
		return (0);
	}
	if ((fd = open(argv[1], O_RDONLY)) == (-1))
	{
		write(2, "unable to read file\n", 20);
		return (-1);
	}
	if ((f = ft_getp(fd)) == NULL)
	{
		close(fd);
		write(2, "incorrect file\n", 15);
		return (-1);
	}
	close(fd);
	window(f);
	return (0);
}
