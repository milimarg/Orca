SRC	=	src/event.cpp \
		src/orca.cpp \
		src/element.cpp \
		src/open.cpp \
		src/getFiles.cpp \
		src/fileElement.cpp \
		src/click.cpp

OBJ	=	$(SRC:.cpp=.o)

NAME	=	liborca.so

TEST	=	test

CPPFLAGS	=	-Wall -Wextra -std=c++20

SFMLFLAGS	=	-L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-system -lsfml-window

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
	g++ -o $(TEST) tests/test.cpp -std=c++20 $(SFMLFLAGS) -L. -lorca

.PHONY: all clean fclean re example
