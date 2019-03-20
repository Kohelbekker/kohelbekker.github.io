# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arykov <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/21 00:12:27 by arykov            #+#    #+#              #
#    Updated: 2018/10/31 18:17:29 by arykov           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1

SRC				= main.c\
				  compute_light.c\
				  draw.c\
				  errors.c\
				  hit_shape.c\
				  list_add.c\
				  parser.c\
				  rotations.c\
				  set_light.c\
				  set_shape.c\
				  shape_elements.c\
				  shape_elements2.c\
				  some_operations.c\
				  trace_ray.c\
				  vector_operations.c\
				  choose_parametr.c\
				  closest_intersaction.c\

SRC_P 			= ./src/
OBJ 			= $(addprefix $(OBJ_P),$(SRC:.c=.o))
OBJ_P			= ./obj/
INC 			= $(addprefix -I, $(INC_P))
INC_P			= ./includes/
HEADER			= $(addprefix $(INC_P), RTv1.h)

LIB_P			= ./libft/
ADD_LIB			= $(addprefix $(LIB_P),libft.a)
INC_LIB			= -I ./libft
LNK_LIB			= -L ./libft -l ft

SDL				= -I ./frameworks/SDL2.framework/Headers/ -F ./frameworks/
FLAGS			= -framework SDL2 -rpath frameworks

# compiler

CC 				= gcc -Wall -Werror -Wextra

all: obj $(ADD_LIB) $(NAME)

obj:
	mkdir -p $(OBJ_P)

$(OBJ_P)%.o:$(SRC_P)%.c $(HEADER)
	$(CC)  $(SDL) $(INC_LIB) -I $(INC_P) -o $@ -c $<

$(ADD_LIB):
	make -C $(LIB_P)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(SDL) $(FLAGS) $(LNK_LIB) -lm -o $(NAME)

clean:
	@rm -rf $(OBJ_P)
	@make -C $(LIB_P) clean
	@printf '\033[31m[ clean ] %s\n\033[0m'

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIB_P) fclean
	@printf '\033[31m[ fclean ] %s\n\033[0m'

re: fclean all

.PHONY: all clean fclean re
