# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/12 18:42:53 by vneelix           #+#    #+#              #
#    Updated: 2020/02/02 13:47:47 by vneelix          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VPATH = ./add_func ./read_file ./space_transforming

INCL = fdf.h

MLX = libmlx.a

INCL_PATH = ./

OBJS = main.o ft_drawline.o keys_events.o plot_gen.o ft_bzero.o ft_memcpy.o \
ft_strjoin.o ft_strlen.o ft_strsplit.o ft_strtol.o file_valid.o ft_getfile.o ft_getp.o mlx_prepare.o ft_transform.o transform_manager.o

CFLAGS = -Wall -Wextra -Werror -c -I$(INCL_PATH)

NAME = fdf

.PHONY : all clean fclean re

%.o: %.c $(INCL)
	gcc $(CFLAGS) $<

$(NAME): $(OBJS)
	$(MAKE) -C ./mlx/minilibx_macos_sierra
	mv ./mlx/minilibx_macos_sierra/libmlx.a ./
	$(MAKE) clean -C ./mlx/minilibx_macos_sierra
	gcc $(OBJS) -lm -L./ $(MLX) -framework OpenGL -framework AppKit -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS) $(MLX)

fclean: clean
	rm -f $(NAME)

re: fclean all
