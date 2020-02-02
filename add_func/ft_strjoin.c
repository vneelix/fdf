/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 21:14:24 by vneelix           #+#    #+#             */
/*   Updated: 2019/12/02 12:32:16 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char			*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len;
	size_t	len2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if ((__uint128_t)len + (__uint128_t)len2 >= SIZE_MAX)
		return (NULL);
	if ((str = (char*)malloc(sizeof(char) * (len + len2 + 1))) == NULL)
		return (NULL);
	ft_bzero(str, len + len2 + 1);
	ft_memcpy(str, s1, len);
	ft_memcpy(str + len, s2, len2);
	return (str);
}
