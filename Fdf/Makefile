# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aperesad <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/06 16:31:07 by aperesad          #+#    #+#              #
#    Updated: 2018/07/06 19:04:19 by aperesad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

FDFLIB = fdf.h

FLAGS2 = -lm -L libft/ -lft -lmlx -framework OpenGL -framework AppKit

SRC = main.c \
	  fdf_center.c \
	  fdf_draw.c \
	  fdf_hooks.c \
	  fdf_make_map.c \
	  fdf_rotate.c \
	  fdf_translation_scale.c

OBJ = $(patsubst %.c,%.o, $(SRC))

CC = gcc
CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ) $(FDFLIB)
	make -C libft/
	$(CC) $(CFLAGS) -I ./libft/ -c $(SRC)
	$(CC) $(OBJ) $(FLAGS2) -o $(NAME)
%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	make clean -C ./libft
	rm -rf $(OBJ)

fclean: clean
	make fclean -C ./libft
	rm -rf $(NAME)

re: fclean all

