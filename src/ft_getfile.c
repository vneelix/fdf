/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getfile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 13:50:46 by vneelix           #+#    #+#             */
/*   Updated: 2019/12/20 13:29:15 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*ft_getfile(int fd)
{
	long	i;
	char	buff[BUFF_SIZE + 1];
	char	*str;
	void	*ptr;

	if ((str = (char*)malloc(sizeof(char))) == NULL)
		return (NULL);
	ft_bzero(str, 1);
	ft_bzero(buff, BUFF_SIZE + 1);
	while ((i = read(fd, buff, BUFF_SIZE)) > 0)
	{
		if (i == 0)
			break ;
		ptr = str;
		str = ft_strjoin(str, buff);
		free(ptr);
		if (str == NULL)
			return (NULL);
		ft_bzero(buff, BUFF_SIZE + 1);
	}
	if (i == (-1) || str[0] == '\0') {
		free(str);
		return (NULL);
	}
	return (str);
}
