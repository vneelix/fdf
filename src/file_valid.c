/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_valid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 13:55:04 by vneelix           #+#    #+#             */
/*   Updated: 2019/12/12 20:08:39 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		check_hex(char ch)
{
	if (ch < '0' || ch > '9')
	{
		if (ch == 'A' || ch == 'B' || ch == 'C'
			|| ch == 'D' || ch == 'E' || ch == 'F'
				|| ch == 'a' || ch == 'b' || ch == 'c'
					|| ch == 'd' || ch == 'e' || ch == 'f')
			return (0);
	}
	else if (ch >= '0' && ch <= '9')
		return (0);
	return (-1);
}

static int		check_color(char **str)
{
	__uint16_t	c;

	c = 0;
	if (**str != '0' && *(*str + 1) != 'x')
		return (-1);
	*str += 2;
	while (**str != '\0')
	{
		if (c == 8 || (c == 6
			&& check_hex(**str) == (-1)))
			break ;
		if (check_hex(**str) == (-1))
			return (-1);
		c += 1;
		*str += 1;
	}
	if (**str == '\0' || **str == ' '
		|| **str == '\t' || **str == '\n')
		return (0);
	return (-1);
}

static int		check_size(size_t size)
{
	static size_t old_size = 0;

	if (old_size == 0)
		old_size = size;
	if (old_size != size)
		return (-1);
	return (0);
}

static void		skip_spaces(char **file)
{
	while ((**file == ' ' || **file == '\t') && **file != '\0')
		*file += 1;
}

int				file_valid(char *file, size_t *size)
{
	while (*file != '\0')
	{
		*size += 1;
		skip_spaces(&file);
		if (*file == '+' || *file == '-')
			file += 1;
		if (*file < '0' || *file > '9')
			return (-1);
		while (*file >= '0' && *file <= '9' && *file != '\0')
			file += 1;
		if (*file == ',')
			if (++file && check_color(&file) == (-1))
				return (-1);
		skip_spaces(&file);
		if (*file == '\n' || *file == '\0')
		{
			if (check_size(*size) == (-1))
				return (-1);
			*file = *file != '\0' ? ' ' : 0;
			file += *file != '\0' ? 1 : 0;
			*size = (*file != '\0') ? 0 : *size;
		}
	}
	return (0);
}
