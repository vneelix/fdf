/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:01:04 by vneelix           #+#    #+#             */
/*   Updated: 2019/12/08 20:10:29 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_memcpy(void *nmem, const void *mem, size_t size)
{
	while (size-- > 0 && mem != NULL && nmem != NULL)
		*((unsigned char*)nmem++) = *((unsigned char*)mem++);
}
