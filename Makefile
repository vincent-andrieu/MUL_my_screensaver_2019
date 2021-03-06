##
## EPITECH PROJECT, 2019
## makefile
## File description:
## project makefile
##

SRC	=	src/main.c	\
		src/dots_trail/dots_trail.c	\
		src/dots_trail/dt_functions.c	\
		src/game_of_life/game_of_life.c	\
		src/game_of_life/gol_functions.c	\
		src/radar/radar.c	\
		src/radar/entities.c	\
		src/radar/scan.c	\
		src/usage/usage.c

OBJ	=	$(SRC:.c=.o)

NAME	=	my_screensaver

CFLAGS	+=	-I include -Wall -Wextra
LDFLAGS +=	-L lib/my -lmy -L lib/graph -lgraph -lm

CC	=	gcc -l csfml-graphics -l csfml-system -l csfml-window

all:	$(NAME)

$(NAME):	$(OBJ)
	make -C lib/my/
	make -C lib/graph/
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean
