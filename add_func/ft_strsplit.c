/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 15:05:26 by vneelix           #+#    #+#             */
/*   Updated: 2019/12/04 17:15:28 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

size_t			ft_countword(const char *str, char ch)
{
	size_t count;

	count = 0;
	while (*str != '\0')
	{
		while (*str == ch && *str != '\0')
			str += 1;
		count += (*str != '\0') ? 1 : 0;
		while (*str != ch && *str != '\0')
			str += 1;
	}
	return (count);
}

static char		*ft_wordcreate(const char *beg, const char *end)
{
	char	*word;

	if ((word = (char*)malloc(end - beg + 1)) == NULL)
		return (NULL);
	ft_bzero(word, end - beg + 1);
	ft_memcpy(word, beg, end - beg);
	return (word);
}

static void		*ft_del(char **data)
{
	size_t	i;

	i = 0;
	while (data[i] != NULL)
		free(data[i++]);
	free(data);
	return (NULL);
}

char			**ft_strsplit(const char *str, char ch)
{
	size_t		i;
	const char	*beg;
	char		**data;
	size_t		w_count;

	w_count = ft_countword(str, ch);
	if ((data = (char**)malloc(sizeof(*data) * (w_count + 1))) == NULL)
		return (NULL);
	ft_bzero(data, (w_count + 1) * sizeof(data));
	i = 0;
	while (*str != '\0')
	{
		while (*str == ch && *str != '\0')
			str += 1;
		beg = str;
		while (*str != ch && *str != '\0')
			str += 1;
		if (beg == str && *str == '\0')
			break ;
		if ((data[i] = ft_wordcreate(beg, str)) == NULL)
			return (ft_del(data));
		i += 1;
	}
	return (data);
}
