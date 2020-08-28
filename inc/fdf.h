/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 12:10:51 by vneelix           #+#    #+#             */
/*   Updated: 2020/02/02 11:02:15 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define BUFF_SIZE 8192

# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include "SDL2/SDL.h"
# include "SDL2/SDL_keyboard.h"

typedef struct	s_point{
	double		x;
	double		y;
	double		z;
	uint32_t	color;
}				t_point;

typedef struct	s_sdl{
	SDL_Window	*win;
	SDL_Surface	*srf;
}				t_sdl;

typedef struct	s_delta{
	int			x;
	int			y;
	int			z;
	int			mov_x;
	int			mov_y;
	int			mov_z;
	double		a;
	double		b;
	double		c;
}				t_delta;

typedef struct	s_figure{
	t_sdl		sdl;
	size_t		size_x;
	size_t		size_y;
	t_point		*src;
	t_point		*spc;
	t_point		*plt;
	t_point		center;
	t_delta		delta;
	t_point		view_point;
	char		p_type;
}				t_figure;

void			window(t_figure *figure);
int				SDL_Loop(t_figure *f);
void			ft_exit(t_figure *f);

/*
** drawline func
*/
void			draw(t_figure *f);
void			ft_central(t_figure *f);
void			ft_parallel(t_figure *f);

/*
** transform space
*/
void			transform_manager(t_figure *f);
void			scale(t_figure *f);
void			move_f(t_figure *f);
void			rotate_x(t_figure *f);
void			rotate_y(t_figure *f);
void			rotate_z(t_figure *f);

/*
** get points
*/
char			*ft_getfile(int fd);
int				file_valid(char *file, size_t *size);
void			*ft_getp(int fd);
void			delta_init(t_figure *f);
int				mlx_prepare(t_figure *f);

/*
** keys func
*/
void			fdf_init(t_figure *f);
int				key_press(SDL_Keycode keycode, t_figure *f);

/*
** add func
*/
char			*ft_strjoin(char const *s1, char const *s2);
void			ft_bzero(void *mem, size_t size);
void			*ft_memcpy(void *dest, const void *src, size_t n);
size_t			ft_strlen(const char *s);
char			**ft_strsplit(const char *str, char ch);
long			ft_strtol(const char *str);

#endif
