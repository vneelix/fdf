/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 13:28:35 by vneelix           #+#    #+#             */
/*   Updated: 2019/12/20 13:00:48 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void				delta_init(t_figure *f)
{
	f->delta.x = 0;
	f->delta.y = 0;
	f->delta.z = 0;
	if ((2 * f->size_x) <= 1366)
		f->delta.a = 1366 / (2 * f->size_x);
	else
		f->delta.a = (2 * f->size_x) / 1366;
	if ((2 * f->size_y) <= 768)
		f->delta.b = 768 / (2 * f->size_y);
	else
		f->delta.b = (2 * f->size_y) / 768;
	f->delta.c = (int)(f->delta.a / 10 + f->delta.b / 10);
	if (f->delta.c == 0)
		f->delta.c = 1;
	f->center = *(f->src + (f->size_x
		/ 2) + f->size_x * (f->size_y / 2));
	f->delta.mov_x = 683 - (f->center.x * f->delta.a);
	f->delta.mov_y = 384 - (f->center.y * f->delta.b);
	f->delta.mov_z = 0;
}

static void			*ft_free(t_figure *f, char *file, char **point)
{
	void	*ptr;

	if (f != NULL)
	{
		if (f->src != NULL)
			free(f->src);
		if (f->spc != NULL)
			free(f->spc);
		if (f->plt != NULL)
			free(f->plt);
		free(f);
	}
	if (file != NULL)
		free(file);
	if (point != NULL)
	{
		ptr = point;
		while (*point != NULL)
			free(*point++);
		free(ptr);
	}
	return (NULL);
}

static void			get_values(long x, long y, char *point, t_point *f)
{
	int	shift;

	f->x = x;
	f->y = y;
	f->z = ft_strtol(point);
	while (*point >= '0' && *point <= '9')
		point += 1;
	f->color = (*point == ',') ? 0 : 0xFFFFFF;
	if (*point == ',')
	{
		point += 2;
		shift = (*(point + 7) != ' ' && *(point + 7)
			!= '\t' && *(point + 7) != '\0') ? 28 : 20;
		while (shift >= 0 && *point++ != '\0')
		{
			if (*point >= '0' && *point <= '9')
				f->color |= ((*point - 48) << shift);
			else if (*point >= 'A' && *point <= 'F')
				f->color |= ((10 + (*point) - 65) << shift);
			else if (*point >= 'a' && *point <= 'f')
				f->color |= ((10 + (*point) - 97) << shift);
			shift -= 4;
		}
	}
}

static int			fill_struct(t_figure *f, char **point)
{
	size_t		i;
	size_t		c;

	i = 0;
	c = 0;
	while (point[c] != NULL && c != SIZE_MAX)
		c += 1;
	f->src = (t_point*)malloc(sizeof(t_point) * c);
	f->spc = (t_point*)malloc(sizeof(t_point) * c);
	f->plt = (t_point*)malloc(sizeof(t_point) * c);
	f->view_point.x = 1366 / 2;
	f->view_point.y = 768 / 2;
	f->view_point.z = 1000;
	f->p_type = 'p';
	if (mlx_prepare(f) == (-1) || f->src == NULL
		|| f->spc == NULL || f->plt == NULL)
		return (-1);
	f->size_y = ((c / f->size_x) == 0) ? 1 : (c / f->size_x);
	while (i < c)
	{
		get_values((i % f->size_x), (i / f->size_x), point[i], (f->src + i));
		i += 1;
	}
	delta_init(f);
	return (0);
}

void				*ft_getp(int fd)
{
	size_t		size;
	char		*file;
	char		**point;
	t_figure	*figure;

	size = 0;
	if ((file = ft_getfile(fd)) == NULL)
		return (NULL);
	if (file_valid(file, &size) == (-1))
		return (ft_free(NULL, file, NULL));
	if ((point = ft_strsplit(file, ' ')) == NULL)
		return (ft_free(NULL, file, NULL));
	if ((figure = (t_figure*)malloc(sizeof(t_figure))) == NULL)
		return (ft_free(NULL, file, point));
	figure->size_x = size;
	if (fill_struct(figure, point) == (-1))
		return (ft_free(figure, file, point));
	ft_free(NULL, file, point);
	return (figure);
}
