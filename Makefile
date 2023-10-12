SRC	=	src/main.cpp

OBJ	=	$(SRC:.cpp=.o)

NAME	=	liborca.so

TEST	=	test

SFMLFLAGS	=	-L/opt/homebrew/Cellar/sfml/2.6.0/lib -lsfml-graphics -lsfml-system -lsfml-window

all: $(NAME)

$(NAME): $(OBJ)
	g++ -shared -o $(NAME) $(OBJ) $(SFMLFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f $(TEST)

re: fclean all

test:
	g++ -o $(TEST) tests/test.cpp $(SFMLFLAGS) -L. -lorca

.PHONY: all clean fclean re example
