/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 12:53:47 by vneelix           #+#    #+#             */
/*   Updated: 2019/12/08 20:10:26 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_bzero(void *mem, size_t size)
{
	while (size / sizeof(int))
	{
		*((int*)mem) = 0;
		mem = (int*)mem + 1;
		size -= sizeof(int);
	}
	while (size % sizeof(int))
	{
		*((unsigned char*)mem++) = 0;
		size -= sizeof(unsigned char);
	}
}
