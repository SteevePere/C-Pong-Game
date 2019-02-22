CC =	gcc
NAME =	Pong
SRC =	main.c \
	function.c \
	game.c
OBJ =	$(SRC:%.c=%.o)
RM =	rm -f
CFLAGS =	-g3

$(NAME):	$(OBJ)
		$(CC) $(OBJ) -o $(NAME) -lSDL2main -lSDL2_image -lSDL2 -pthread -W -Wall -g3

all:	$(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re:	fclean all
