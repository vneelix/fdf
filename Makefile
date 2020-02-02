# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/12 18:42:53 by vneelix           #+#    #+#              #
#    Updated: 2019/12/21 11:43:02 by vneelix          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VPATH = ./add_func ./read_file ./space_transforming

INCL = fdf.h

INCL_PATH = ./

OBJS = main.o ft_drawline.o keys_events.o plot_gen.o ft_bzero.o ft_memcpy.o \
ft_strjoin.o ft_strlen.o ft_strsplit.o ft_strtol.o file_valid.o ft_getfile.o ft_getp.o mlx_prepare.o ft_transform.o transform_manager.o

CFLAGS = -Wall -Wextra -Werror -c -I$(INCL_PATH)

NAME = fdf

.PHONY : all clean fclean re

%.o: %.c $(INCL)
	gcc $(CFLAGS) $<

$(NAME): $(OBJS)
	gcc $(OBJS) -lm -lmlx -framework OpenGL -framework AppKit -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
