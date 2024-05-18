SRC	=	src/Orca.cpp \
		src/FileElement.cpp \
		src/Element.cpp

OBJ	=	$(SRC:.cpp=.o)

NAME	=	liborca.so

TEST	=	test

CPPFLAGS	=	-Wall -Wextra -std=c++20 -fPIC -g

SFMLFLAGS	=	-lsfml-graphics -lsfml-system -lsfml-window

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
	g++ -o $(TEST) tests/test.cpp $(SFMLFLAGS) $(CPPFLAGS) -L. -lorca

.PHONY: all clean fclean re test
