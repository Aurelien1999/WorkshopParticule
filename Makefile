##
## EPITECH PROJECT, 2018
## make
## File description:
## ..
##

CC = gcc

SRC = particle.c
	  
OBJ = $(SRC:.c=.o)

NAME = part

RM = rm -rf

CFLAGS = -lcsfml-graphics -lcsfml-system -lcsfml-window -lcsfml-audio -lm

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean:		clean
	$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re test