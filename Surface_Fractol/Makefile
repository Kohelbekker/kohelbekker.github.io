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

NAME = fractol

FRLIB = fractol.h

FLAGS2 = -L /Users/aperesad/.brew/Cellar/sdl2/2.0.9/lib -L libft/ -lft -lSDL2

SRC = main.c \
	  fractals1.c \
	  fractals2.c \
	  mouse_jul.c \
	  zoom.c \
	  draw.c \
	  errors.c \
	  hooks.c \
	  init.c \

OBJ = $(patsubst %.c,%.o, $(SRC))

CC = gcc
CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ) $(FRLIB)
	@make -C libft/
	@$(CC) $(CFLAGS) $(FLAGS2) $(SRC) -o $(NAME)
	@printf '\033[32m[ Done ] %s\n\033[0m'
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "Compiling $@\n"

clean:
	@make clean -C ./libft
	@rm -rf $(OBJ)
	@printf '\033[31m[ clean ] %s\n\033[0m'

fclean: clean
	@make fclean -C ./libft
	@rm -rf $(NAME)
	@printf '\033[31m[ fclean ] %s\n\033[0m'

re: fclean all

.PHONY: clean fclean re all