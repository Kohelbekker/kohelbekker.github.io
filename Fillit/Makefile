# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aperesad <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 19:10:59 by aperesad          #+#    #+#              #
#    Updated: 2017/11/21 17:37:20 by aperesad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= fillit
CFLAGS		= -Wall -Werror -Wextra

all: $(NAME)


$(NAME): main.o pst.o ret.o trypst.o
	gcc $(CFLAGS) main.o pst.o ret.o trypst.o -o fillit

main.o: main.c
	gcc $(CFLAGS) -c main.c

pst.o: pst.c
	gcc $(CFLAGS) -c pst.c

ret.o: ret.c
	gcc $(CFLAGS) -c ret.c

trypst.o: trypst.c
	gcc $(CFLAGS) -c trypst.c

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all