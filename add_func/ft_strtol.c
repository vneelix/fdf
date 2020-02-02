/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 18:05:07 by vneelix           #+#    #+#             */
/*   Updated: 2019/11/17 14:04:35 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static const char			*ft_strtol_check(const char *str, int *f)
{
	while (*str == '\t' || *str == '\v' || *str == '\f' ||
			*str == '\r' || *str == '\n' || *str == ' ')
		str += 1;
	if (*str == '+' || *str == '-')
	{
		*f = 1;
		str += 1;
	}
	if (*str < '0' || *str > '9')
		return (NULL);
	return (str);
}

long						ft_strtol(const char *str)
{
	int				f;
	unsigned long	num;

	f = 0;
	str = ft_strtol_check(str, &f);
	if (str == NULL)
		return (0);
	num = 0;
	while (*str >= '0' && *str <= '9')
	{
		if (num >= 1000000000000000000UL)
			return (0);
		num = num * 10 + ((unsigned long long)(*str) - 48);
		str++;
	}
	if (num > INT64_MAX && f == 0)
		return (-1);
	else if (num > (((unsigned long)INT64_MAX) + 1) && f == 1)
		return (0);
	return (num);
}
